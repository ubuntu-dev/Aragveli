/*
 * Copyright (c) 2017 Konstantin Tcholokachvili.
 * All rights reserved.
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include <lib/queue.h>
#include <lib/c/assert.h>
#include <memory/frame.h>
#include "heap.h"

uint32_t heap = 0;

SLIST_HEAD(, memory_range) free_ranges;
SLIST_HEAD(, memory_range) used_ranges;

struct memory_range
{
	uint32_t base_address;
	uint32_t nb_pages;
	SLIST_ENTRY(memory_range) next;
};

static void
create_range(bool is_free, vaddr_t start_address, vaddr_t end_address)
{
	assert(IS_PAGE_ALIGNED(start_address));
	assert(IS_PAGE_ALIGNED(end_address));

	if ((end_address - start_address) < PAGE_SIZE)
		return;

	struct memory_range *range = (struct memory_range *)heap;
	heap += sizeof(struct memory_range);

	assert(range != NULL);

	range->base_address = start_address;
	range->nb_pages = (end_address - start_address) / PAGE_SIZE;

	if (is_free)
		SLIST_INSERT_HEAD(&free_ranges, range, next);
	else
		SLIST_INSERT_HEAD(&used_ranges, range, next);
}

void
heap_setup(vaddr_t identity_mapping_start,
		vaddr_t identity_mapping_end,
		uint32_t framebuffer_start,
		uint32_t framebuffer_end)
{
	SLIST_INIT(&free_ranges);
	SLIST_INIT(&used_ranges);

	// For heap management
	map_pages(PAGE_ALIGN_UP(identity_mapping_end),
			identity_mapping_end + PAGE_SIZE,
			false);

	heap = PAGE_ALIGN_UP(identity_mapping_end);

	// Free: 16 Kb - Framebuffer
	create_range(true,
			VM_BASE,
			PAGE_ALIGN_DOWN(framebuffer_start));

	// Used: Framebuffer zone
	create_range(false,
			PAGE_ALIGN_DOWN(framebuffer_start),
			PAGE_ALIGN_UP(framebuffer_end));

	// Free: Framebuffer end - Kernel start
	create_range(true,
			PAGE_ALIGN_UP(framebuffer_end),
			PAGE_ALIGN_DOWN(identity_mapping_start));

	// Used: Kernel
	create_range(false,
			PAGE_ALIGN_UP(identity_mapping_start),
			PAGE_ALIGN_DOWN(identity_mapping_end));

	// Used: Heap's allocation zone
	create_range(false,
			PAGE_ALIGN_UP(identity_mapping_end),
			PAGE_ALIGN_DOWN(identity_mapping_end + PAGE_SIZE));

	// Free: Heap's allocation zone - Kernel end
	create_range(true,
			PAGE_ALIGN_UP(identity_mapping_end + PAGE_SIZE),
			VM_TOP);
}

void
map_pages(vaddr_t base_address,
		vaddr_t top_address,
		bool is_user_page)
{
	vaddr_t va;
	paddr_t pa;

	for (va = base_address;
		va < top_address;
		va += PAGE_SIZE)
	{
		pa = frame_alloc();

		assert(pa != (paddr_t)NULL);

		status_t status = paging_map(pa, va, is_user_page,
			VM_MAP_ATOMIC | VM_MAP_PROT_READ | VM_MAP_PROT_WRITE);

		assert(status == KERNEL_OK);

		/* This page is already mapped, so it can be unreferenced.
		   It's reference_counter should = 1 at this step
		   when mapped first time */
		frame_free(pa);
	}
}

void
unmap_pages(vaddr_t base_address, vaddr_t top_address)
{
	vaddr_t va;

	for (va = base_address;
		va < top_address;
		va += PAGE_SIZE)
    {
	    assert(paging_unmap(va) == KERNEL_OK);
    }
}

void *
heap_alloc(size_t size)
{
	struct memory_range *range;
	size_t nb_requested_pages;

	if (SLIST_EMPTY(&free_ranges))
		return NULL;

	nb_requested_pages = size < PAGE_SIZE ? 1 : size / PAGE_SIZE;

	SLIST_FOREACH(range, &free_ranges, next)
	{
		if (range->nb_pages >= nb_requested_pages)
		{
			// Resize this range ?
			if (range->nb_pages > nb_requested_pages)
			{
				range->nb_pages -= nb_requested_pages;

				// New range
				struct memory_range *new_range =
					(struct memory_range *)heap;

				heap += sizeof(struct memory_range);

				new_range->base_address = range->base_address
					+ range->nb_pages * PAGE_SIZE;
				new_range->nb_pages = nb_requested_pages;

				SLIST_INSERT_HEAD(&used_ranges, new_range, next);

				map_pages(new_range->base_address,
					new_range->base_address
					+ new_range->nb_pages * PAGE_SIZE,
					false);

				return (void *)new_range->base_address;
			}
			else
			{
				SLIST_REMOVE(&free_ranges, range,
						memory_range, next);
				SLIST_INSERT_HEAD(&used_ranges, range, next);

				map_pages(range->base_address,
					range->base_address
					+ range->nb_pages * PAGE_SIZE,
					false);

				return (void *)range->base_address;
			}
		}
	}

	return NULL;
}

void
heap_free(void *address)
{
	struct memory_range *range;

	if (!address)
		return;

	SLIST_FOREACH(range, &used_ranges, next)
	{
		if (range->base_address == (uint32_t)address)
		{
			SLIST_REMOVE(&used_ranges, range, memory_range, next);

			unmap_pages(range->base_address,
				range->base_address
				+ range->nb_pages * PAGE_SIZE);

			SLIST_INSERT_HEAD(&free_ranges, range, next);
		}
	}
}
