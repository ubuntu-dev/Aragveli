/*
 * Copyright (c) 2015, 2017 Konstantin Tcholokachvili.
 * All rights reserved.
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include <fs/tarfs.h>
#include <fs/vfs.h>
#include <lib/c/string.h>
#include <lib/c/stdlib.h>
#include <lib/c/stdio.h>
#include <lib/c/assert.h>
#include <lib/types.h>
#include <lib/queue.h>
#include "tarfs.h"

/* TMPFS node operations */
node_ops_t tarfs_node_ops =
{
	.root_get     = NULL,
	.match        = NULL,
	.node_get     = NULL,
	.node_open    = NULL,
	.node_put     = NULL,
	.create       = NULL,
	.destroy      = NULL,
	.link         = NULL,
	.unlink       = NULL,
	.has_children = NULL,
	.index_get    = NULL,
	.size_get     = NULL,
	.lnkcnt_get   = NULL,
	.is_directory = NULL,
	.is_file      = NULL
};

static struct file_system tarfs;
static char *remaining_path;
static vaddr_t initrd_start, initrd_end;

static char *
strip_slashes(char *path)
{
	int i = 0;
	static char path_item[255]; // Limited to 255 characters
	char *tmp;

	if (path == NULL)
		tmp = remaining_path;
	else
		tmp = path;

	memset(path_item, 0, strlen(path_item));

	while (*++tmp)
		if (*tmp != '/')
			break;
	tmp--;

	while (*++tmp)
		if (*tmp == '/')
			break;
		else
			path_item[i++] = *tmp;

	remaining_path = tmp;

	if (*tmp == '\0' && strlen(path_item) == 0)
	{
		remaining_path = NULL;
		return NULL;
	}
	else
	{
		return path_item;
	}
}

/* Parse an octal number, ignoring leading and trailing nonsense. */
static int
parseoct(const char *p, size_t n)
{
	int i = 0;

	while (*p < '0' || *p > '7')
	{
		++p;
		--n;
	}

	while (*p >= '0' && *p <= '7' && n > 0)
	{
		i *= 8;
		i += *p - '0';
		++p;
		--n;
	}
	return i;
}

/* Returns true if this is 512 zero bytes. */
static int
is_end_of_archive(const char *p)
{
	int n;
	for (n = 511; n >= 0; --n)
		if (p[n] != '\0')
			return 0;
	return 1;
}

/* Verify tar archive's checksum. */
static int
checksum(const char *p)
{
	int n, u = 0;
	for (n = 0; n < 512; ++n) {
		if (n < 148 || n > 155)
			/* Standard tar checksum adds unsigned bytes. */
			u += ((unsigned char *)p)[n];
		else
			u += 0x20;

	}
	return (u == parseoct(p + 148, 8));
}

struct dentry *
resolve_node(char *path, struct dentry *root_node)
{
	struct dentry *tmp_node, *node;
	char *path_item;
	bool found = false;

	char *complete_path = malloc(strlen(path)+1);

	if (!complete_path)
		return NULL;

	strzcpy(complete_path, path, strlen(path)+1);

	path_item = strip_slashes(complete_path);
	tmp_node = root_node;

	while (path_item != NULL)
	{
		LIST_FOREACH(node, &tmp_node->u.dir.nodes, next)
		{
			if (strncmp(path_item, node->name, strlen(node->name)+1) == 0)
			{
				tmp_node = node;
				found = true;
			}
		}

		if (!found)
		{
			tmp_node = NULL;
			break;
		}

		path_item = strip_slashes(NULL);
	}

	//free(complete_path); FIXME

	return tmp_node;
}

static char *
tarfs_basename(char *path)
{
	char *last_slash = strrchr(path, '/');

	if (!last_slash)
		return NULL;

	if (!(strlen(last_slash) == 1 && last_slash[0] == '/'))
		++last_slash; // Remove the leading slash by the way

	return last_slash;
}

static char *
tarfs_dirname(char *path)
{
	char *last_slash = strrchr(path, '/');

	if (!last_slash)
		return NULL;

	int new_path_length = strlen(path) - strlen(last_slash) + 1;
	char *new_path = malloc(new_path_length);

	if (!new_path)
		return NULL;

	strzcpy(new_path, path, new_path_length+1);

	return new_path;
}

static status_t
add_node(char *path, uint8_t type, int file_size, void *archive,
		struct dentry *root_node)
{
	if (type == TMPFS_DIRECTORY)
	{
		// Strip trailing '/' for no root directories
		if (strlen(path) > 1 && path[strlen(path) - 1] == '/')
			path[strlen(path) - 1] = '\0';

		char *directory_dirname = tarfs_dirname(path);
		char *directory_basename = tarfs_basename(path);

		struct dentry *parent_node = resolve_node(directory_dirname,
				root_node);

		if (!parent_node)
			return -KERNEL_NO_SUCH_FILE_OR_DIRECTORY;

		struct dentry *dir_node = malloc(sizeof(struct dentry));

		if (!dir_node)
			return -KERNEL_NO_MEMORY;

		memset(dir_node, 0, sizeof(struct dentry));

		dir_node->type = TMPFS_DIRECTORY;
		dir_node->name_length = strlen(directory_basename)+1;
		strzcpy(dir_node->name,
				directory_basename,
				dir_node->name_length);

		// Don't report '/'
		if (!strncmp(parent_node->name, "/", strlen("/"))
				&& !strncmp(dir_node->name, "/", strlen("/")))
			return KERNEL_OK;

		LIST_INSERT_HEAD(&(parent_node->u.dir.nodes), dir_node, next);
	}
	else if (type == TMPFS_FILE)
	{
		char *directory_dirname = tarfs_dirname(path);
		char *directory_basename = tarfs_basename(path);

		struct dentry *parent_node = resolve_node(directory_dirname,
				root_node);

		if (!parent_node)
			return -KERNEL_NO_SUCH_FILE_OR_DIRECTORY;

		struct dentry *file_node = malloc(sizeof(struct dentry));

		if (!file_node)
			return -KERNEL_NO_MEMORY;

		file_node->type = TMPFS_FILE;
		file_node->name_length = strlen(directory_basename)+1;
		strzcpy(file_node->name,
				directory_basename,
				file_node->name_length);
		file_node->u.file.size = file_size;
		file_node->u.file.data = archive - 512;

		LIST_INSERT_HEAD(&(parent_node->u.dir.nodes), file_node, next);
	}

	return KERNEL_OK;
}

static void
untar(void *ramdisk_address, struct dentry *root_node)
{
	char buff[512];
	int file_size;
	status_t status;

	while (1)
	{
		memcpy(buff, ramdisk_address, 512);
		ramdisk_address += 512;

		if (is_end_of_archive(buff))
			return;

		if (!checksum(buff))
		{
			printf("Checksum failure\n");
			return;
		}

		if (buff[156] == '0' || buff[156] == '7')
		{
			file_size = parseoct(buff + 124, 12);

			if (file_size < 512)
				file_size = 512;

			ramdisk_address += file_size;

			char *normalized_path = strchr(buff, '/');

			status = add_node(normalized_path, TMPFS_FILE,
					file_size, ramdisk_address, root_node);
			assert(status == KERNEL_OK);
		}
		else if (buff[156] == '5')
		{
			char *normalized_path = strchr(buff, '/');

			status = add_node(normalized_path, TMPFS_DIRECTORY, 0,
					ramdisk_address, root_node);
			assert(status == KERNEL_OK);
		}
	}
}

static status_t
tarfs_mount(const char *root_device, const char *mount_point,
		const char *mount_args, struct superblock **result_rootfs)
{
	void *ramdisk_address = (void *)initrd_start;
	(void)root_device;
	(void)mount_point;
	(void)mount_args;

	struct dentry *root_node = malloc(sizeof(struct dentry));

	if (!root_node)
		return -KERNEL_NO_MEMORY;

	root_node->type = TMPFS_DIRECTORY;
	root_node->name_length = strlen("/")+1;
	strzcpy(root_node->name, "/", root_node->name_length);

	LIST_INIT(&(root_node->u.dir.nodes));
	untar(ramdisk_address, root_node);

	struct superblock *tarfs_superblock = malloc(sizeof(struct superblock));

	if (!tarfs_superblock)
		return -KERNEL_NO_MEMORY;

	tarfs_superblock->root = root_node;
	*result_rootfs = tarfs_superblock;

	return KERNEL_OK;
}

static status_t
tarfs_umount(void)
{
	return KERNEL_OK;
}

status_t
tarfs_init(vaddr_t start, vaddr_t end)
{
	strzcpy(tarfs.name, "tarfs", strlen("tarfs")+1);
	tarfs.mount  = tarfs_mount;
	tarfs.umount = tarfs_umount;

	initrd_start = start;
	initrd_end   = end;

	return fs_register(&tarfs);
}


vfs_ops_t
tarfs_ops = {
	.mount    = tarfs_mount,
	.umount   = tarfs_umount,
	.read     = NULL,
	.write    = NULL,
	.truncate = NULL,
	.close    = NULL,
	.destroy  = NULL,
	.sync     = NULL
};
