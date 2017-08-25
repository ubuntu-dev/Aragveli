/*
 * Copyright (c) 2017 Konstantin Tcholokachvili.
 * All rights reserved.
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once

#include <lib/types.h>

#define NORMAL_BLACK	0x000000
#define NORMAL_RED	0xAA0000
#define NORMAL_GREEN	0x00AA00
#define NORMAL_YELLOW	0xAAAA00
#define NORMAL_BLUE	0x0000AA
#define NORMAL_MAGENTA	0xAA00AA
#define NORMAL_CYAN	0x00AAAA
#define NORMAL_WHITE	0xAAAAAA
#define BRIGHT_BLACK	0x555555
#define BRIGHT_RED	0xFF5555
#define BRIGHT_GREEN	0x55FF55
#define BRIGHT_YELLOW	0xFFFF55
#define BRIGHT_BLUE	0x5555FF
#define BRIGHT_MAGENTA	0xFF55FF
#define BRIGHT_CYAN	0x55FFFF
#define BRIGHT_WHITE	0xFFFFFF

struct vbe_mode_info
{
	uint16_t mode_attr;
	uint8_t winA_attr;
	uint8_t winB_attr;
	uint16_t win_granul;
	uint16_t win_size;
	uint16_t winA_seg;
	uint16_t winB_seg;
	uint32_t win_func_addr;
	uint16_t pitch;
	uint16_t x_res;
	uint16_t y_res;
	uint8_t x_char_size;
	uint8_t y_char_size;
	uint8_t planes;
	uint8_t bpp;
	uint8_t banks;
	uint8_t memmodel;
	uint8_t bank_size;
	uint8_t img_pages;
	uint8_t reserved0;
	uint8_t red_mask_size;
	uint8_t red_field_pos;
	uint8_t green_mask_size;
	uint8_t green_field_pos;
	uint8_t blue_mask_size;
	uint8_t blue_field_pos;
	uint8_t reserved_mask_size;
	uint8_t reserved_field_pos;
	uint8_t direct_color_attr;
	uint32_t framebuffer_addr;
	uint32_t reserved1;
	uint16_t reserved2;
	uint16_t lin_pitch;
	uint8_t bnk_img_pages;
	uint8_t lin_img_pages;
	uint8_t lin_red_mask_size;
	uint8_t lin_red_field_pos;
	uint8_t lin_green_mask_size;
	uint8_t lin_green_field_pos;
	uint8_t lin_blue_mask_size;
	uint8_t lin_blue_field_pos;
	uint8_t lin_reserved_mask_size;
	uint8_t lin_reserved_field_pos;
	uint32_t max_pixel_clock;
} __attribute__((packed));

struct vbe_ctrl_info
{
	uint32_t signature;
	uint16_t version;
	uint32_t oem_str_addr;
	uint32_t capabilities;
	uint32_t video_mode_addr;
	uint16_t blocks;
	uint16_t oem_software_revision;
	uint32_t oem_vendor_name_addr;
	uint32_t oem_product_name_addr;
	uint32_t oem_product_revision_addr;
} __attribute__((packed));

static const unsigned char font[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x38,0x44,0x82,0xaa,0xaa,0x82,0x82,0xaa,0x92,0x44,0x38,0x00,0x00,0x00,
	0x00,0x00,0x38,0x7c,0xfe,0xd6,0xd6,0xfe,0xfe,0xd6,0xee,0x7c,0x38,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x6c,0xfe,0xfe,0xfe,0x7c,0x38,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x38,0x7c,0xfe,0x7c,0x38,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x38,0x54,0xfe,0x54,0x10,0x38,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x38,0x7c,0xfe,0xd6,0x10,0x38,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3c,0x3c,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xff,0xe7,0xc3,0xc3,0xe7,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0x00,0x00,0x00,0x00,0x3c,0x66,0x42,0x42,0x66,0x3c,0x00,0x00,0x00,0x00,0x00,
	0xff,0xff,0xff,0xff,0xff,0xc3,0x99,0xbd,0xbd,0x99,0xc3,0xff,0xff,0xff,0xff,0xff,
	0x00,0x10,0x38,0x54,0x92,0x10,0x10,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x10,0x10,0xfe,0x10,0x10,0x10,0x00,0x00,
	0x00,0x00,0x0c,0x0e,0x0b,0x0b,0x0a,0x08,0x08,0x18,0x78,0xf8,0x70,0x00,0x00,0x00,
	0x00,0x00,0x1f,0x1f,0x11,0x11,0x11,0x11,0x11,0x11,0x77,0xff,0x66,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x54,0x38,0x28,0x38,0x54,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00,0x00,
	0x00,0x02,0x06,0x0e,0x1e,0x3e,0x7e,0xfe,0x7e,0x3e,0x1e,0x0e,0x06,0x02,0x00,0x00,
	0x00,0x00,0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x92,0x54,0x38,0x10,0x00,0x00,0x00,
	0x00,0x00,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x00,0x00,0x44,0x44,0x00,0x00,
	0x00,0x3e,0x4a,0x8a,0x8a,0x8a,0x8a,0x4a,0x3a,0x0a,0x0a,0x0a,0x0a,0x0a,0x00,0x00,
	0x7c,0x82,0x40,0x20,0x38,0x44,0x82,0x82,0x82,0x44,0x38,0x08,0x04,0x82,0x7c,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0xfe,0xfe,0x00,0x00,
	0x00,0x00,0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x92,0x54,0x38,0x10,0x7c,0x00,0x00,
	0x00,0x10,0x38,0x54,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x92,0x54,0x38,0x10,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x08,0x04,0xfe,0x04,0x08,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x20,0x40,0xfe,0x40,0x20,0x10,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xfe,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x28,0x44,0xfe,0x44,0x28,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x10,0x38,0x38,0x7c,0x7c,0xfe,0xfe,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xfe,0xfe,0x7c,0x7c,0x38,0x38,0x10,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x10,0x10,0x00,0x00,
	0x28,0x28,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x44,0x44,0x44,0xfe,0x44,0x44,0x44,0x44,0x44,0xfe,0x44,0x44,0x44,0x00,0x00,
	0x10,0x3a,0x56,0x92,0x92,0x90,0x50,0x38,0x14,0x12,0x92,0x92,0xd4,0xb8,0x10,0x10,
	0x62,0x92,0x94,0x94,0x68,0x08,0x10,0x10,0x20,0x2c,0x52,0x52,0x92,0x8c,0x00,0x00,
	0x00,0x70,0x88,0x88,0x88,0x90,0x60,0x47,0xa2,0x92,0x8a,0x84,0x46,0x39,0x00,0x00,
	0x04,0x08,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00,
	0x80,0x40,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x20,0x40,0x80,0x00,
	0x00,0x00,0x00,0x00,0x00,0x10,0x92,0x54,0x38,0x54,0x92,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0xfe,0x10,0x10,0x10,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08,0x08,0x10,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
	0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x80,0x80,
	0x00,0x18,0x24,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x24,0x18,0x00,0x00,
	0x00,0x08,0x18,0x28,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x3e,0x00,0x00,
	0x00,0x18,0x24,0x42,0x42,0x02,0x04,0x08,0x10,0x20,0x20,0x40,0x40,0x7e,0x00,0x00,
	0x00,0x18,0x24,0x42,0x02,0x02,0x04,0x18,0x04,0x02,0x02,0x42,0x24,0x18,0x00,0x00,
	0x00,0x0c,0x0c,0x0c,0x14,0x14,0x14,0x24,0x24,0x44,0x7e,0x04,0x04,0x1e,0x00,0x00,
	0x00,0x7c,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x02,0x02,0x42,0x24,0x18,0x00,0x00,
	0x00,0x18,0x24,0x42,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,
	0x00,0x7e,0x42,0x42,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x24,0x18,0x00,0x00,
	0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x26,0x1a,0x02,0x42,0x24,0x18,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x08,0x08,0x10,
	0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,0x00,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00,
	0x00,0x38,0x44,0x82,0x82,0x82,0x04,0x08,0x10,0x10,0x00,0x00,0x18,0x18,0x00,0x00,
	0x00,0x38,0x44,0x82,0x9a,0xaa,0xaa,0xaa,0xaa,0xaa,0x9c,0x80,0x46,0x38,0x00,0x00,
	0x00,0x18,0x18,0x18,0x18,0x24,0x24,0x24,0x24,0x7e,0x42,0x42,0x42,0xe7,0x00,0x00,
	0x00,0xf0,0x48,0x44,0x44,0x44,0x48,0x78,0x44,0x42,0x42,0x42,0x44,0xf8,0x00,0x00,
	0x00,0x3a,0x46,0x42,0x82,0x80,0x80,0x80,0x80,0x80,0x82,0x42,0x44,0x38,0x00,0x00,
	0x00,0xf8,0x44,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x44,0xf8,0x00,0x00,
	0x00,0xfe,0x42,0x42,0x40,0x40,0x44,0x7c,0x44,0x40,0x40,0x42,0x42,0xfe,0x00,0x00,
	0x00,0xfe,0x42,0x42,0x40,0x40,0x44,0x7c,0x44,0x44,0x40,0x40,0x40,0xf0,0x00,0x00,
	0x00,0x3a,0x46,0x42,0x82,0x80,0x80,0x9e,0x82,0x82,0x82,0x42,0x46,0x38,0x00,0x00,
	0x00,0xe7,0x42,0x42,0x42,0x42,0x42,0x7e,0x42,0x42,0x42,0x42,0x42,0xe7,0x00,0x00,
	0x00,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x00,0x00,
	0x00,0x1f,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x84,0x48,0x30,0x00,
	0x00,0xe7,0x42,0x44,0x48,0x50,0x50,0x60,0x50,0x50,0x48,0x44,0x42,0xe7,0x00,0x00,
	0x00,0xf0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0x42,0xfe,0x00,0x00,
	0x00,0xc3,0x42,0x66,0x66,0x66,0x5a,0x5a,0x5a,0x42,0x42,0x42,0x42,0xe7,0x00,0x00,
	0x00,0xc7,0x42,0x62,0x62,0x52,0x52,0x52,0x4a,0x4a,0x4a,0x46,0x46,0xe2,0x00,0x00,
	0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0xf8,0x44,0x42,0x42,0x42,0x44,0x78,0x40,0x40,0x40,0x40,0x40,0xf0,0x00,0x00,
	0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x92,0x8a,0x44,0x3a,0x00,0x00,
	0x00,0xfc,0x42,0x42,0x42,0x42,0x7c,0x44,0x42,0x42,0x42,0x42,0x42,0xe7,0x00,0x00,
	0x00,0x3a,0x46,0x82,0x82,0x80,0x40,0x38,0x04,0x02,0x82,0x82,0xc4,0xb8,0x00,0x00,
	0x00,0xfe,0x92,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x00,0x00,
	0x00,0xe7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x3c,0x00,0x00,
	0x00,0xe7,0x42,0x42,0x42,0x42,0x24,0x24,0x24,0x24,0x18,0x18,0x18,0x18,0x00,0x00,
	0x00,0xe7,0x42,0x42,0x42,0x5a,0x5a,0x5a,0x5a,0x24,0x24,0x24,0x24,0x24,0x00,0x00,
	0x00,0xe7,0x42,0x42,0x24,0x24,0x24,0x18,0x24,0x24,0x24,0x42,0x42,0xe7,0x00,0x00,
	0x00,0xee,0x44,0x44,0x44,0x28,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x7c,0x00,0x00,
	0x00,0xfe,0x84,0x84,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x42,0x82,0xfe,0x00,0x00,
	0x00,0x3e,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x3e,0x00,
	0x80,0x80,0x40,0x40,0x20,0x20,0x20,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x02,0x02,
	0x00,0x7c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x7c,0x00,
	0x00,0x10,0x28,0x44,0x82,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x00,
	0x10,0x08,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x70,0x08,0x04,0x3c,0x44,0x84,0x84,0x8c,0x76,0x00,0x00,
	0xc0,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x64,0x58,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x30,0x4c,0x84,0x84,0x80,0x80,0x82,0x44,0x38,0x00,0x00,
	0x0c,0x04,0x04,0x04,0x04,0x34,0x4c,0x84,0x84,0x84,0x84,0x84,0x4c,0x36,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0xfc,0x80,0x82,0x42,0x3c,0x00,0x00,
	0x0e,0x10,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7c,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x36,0x4c,0x84,0x84,0x84,0x84,0x4c,0x34,0x04,0x04,0x78,
	0xc0,0x40,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0xe3,0x00,0x00,
	0x00,0x10,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x04,0x04,0x00,0x00,0x0c,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x08,0x08,0x30,
	0xc0,0x40,0x40,0x40,0x40,0x4e,0x44,0x48,0x50,0x60,0x50,0x48,0x44,0xe6,0x00,0x00,
	0x30,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xf6,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0xdb,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xd8,0x64,0x42,0x42,0x42,0x42,0x42,0x42,0xe3,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xd8,0x64,0x42,0x42,0x42,0x42,0x42,0x64,0x58,0x40,0xe0,
	0x00,0x00,0x00,0x00,0x00,0x34,0x4c,0x84,0x84,0x84,0x84,0x84,0x4c,0x34,0x04,0x0e,
	0x00,0x00,0x00,0x00,0x00,0xdc,0x62,0x42,0x40,0x40,0x40,0x40,0x40,0xe0,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x7a,0x86,0x82,0xc0,0x38,0x06,0x82,0xc2,0xbc,0x00,0x00,
	0x00,0x00,0x10,0x10,0x10,0x7c,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x0e,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xc6,0x42,0x42,0x42,0x42,0x42,0x42,0x46,0x3b,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xe7,0x42,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xe7,0x42,0x42,0x5a,0x5a,0x5a,0x24,0x24,0x24,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xc6,0x44,0x28,0x28,0x10,0x28,0x28,0x44,0xc6,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0xe7,0x42,0x42,0x24,0x24,0x24,0x18,0x18,0x10,0x10,0x60,
	0x00,0x00,0x00,0x00,0x00,0xfe,0x82,0x84,0x08,0x10,0x20,0x42,0x82,0xfe,0x00,0x00,
	0x00,0x06,0x08,0x10,0x10,0x10,0x10,0x60,0x10,0x10,0x10,0x10,0x08,0x06,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x00,0x60,0x10,0x08,0x08,0x08,0x08,0x06,0x08,0x08,0x08,0x08,0x10,0x60,0x00,0x00,
	0x00,0x72,0x8c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x28,0x44,0x82,0xfe,0x82,0xfe,0x00,0x00,0x00,0x00,0x00,
	0x00,0x38,0x44,0x82,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x82,0x44,0x38,0x10,0x20,
	0x00,0x00,0x24,0x24,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x00,0x00,
	0x0c,0x08,0x10,0x00,0x00,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x00,0x00,
	0x00,0x10,0x28,0x44,0x00,0x78,0x04,0x04,0x3c,0x44,0x84,0x84,0x44,0x3e,0x00,0x00,
	0x00,0x00,0x24,0x24,0x00,0x78,0x04,0x04,0x3c,0x44,0x84,0x84,0x44,0x3e,0x00,0x00,
	0x10,0x08,0x04,0x00,0x00,0x78,0x04,0x04,0x3c,0x44,0x84,0x84,0x44,0x3e,0x00,0x00,
	0x00,0x18,0x24,0x18,0x00,0x78,0x04,0x04,0x3c,0x44,0x84,0x84,0x44,0x3e,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x3c,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x3c,0x08,0x10,
	0x00,0x10,0x28,0x44,0x00,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x00,0x00,
	0x00,0x00,0x24,0x24,0x00,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x00,0x00,
	0x10,0x08,0x04,0x00,0x00,0x38,0x44,0x82,0x82,0xfe,0x80,0x82,0x44,0x38,0x00,0x00,
	0x00,0x00,0x24,0x24,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0x10,0x28,0x44,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x10,0x08,0x04,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x24,0x24,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0xfe,0x82,0x82,0x82,0x82,0x00,0x00,
	0x00,0x38,0x44,0x38,0x44,0x82,0x82,0x82,0x82,0xfe,0x82,0x82,0x82,0x82,0x00,0x00,
	0x0c,0x08,0x10,0xfe,0x80,0x80,0x80,0x80,0xf8,0x80,0x80,0x80,0x80,0xfe,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x60,0x1c,0x12,0x72,0x9e,0x90,0x90,0x92,0x6c,0x00,0x00,
	0x0c,0x10,0x20,0x28,0x28,0x28,0xfe,0x28,0x28,0x28,0x28,0x28,0x28,0x28,0x00,0x00,
	0x00,0x10,0x28,0x44,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0x00,0x24,0x24,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x10,0x08,0x04,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0x10,0x28,0x44,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x00,0x00,
	0x10,0x08,0x04,0x00,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x00,0x00,
	0x00,0x00,0x24,0x24,0x00,0x82,0x82,0x44,0x44,0x28,0x28,0x10,0x10,0x20,0x20,0x40,
	0x24,0x24,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x24,0x24,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0x28,0x28,0x28,0x3c,0x6a,0xa8,0xa8,0xa8,0xa8,0xa8,0x6a,0x3c,0x28,0x28,0x28,
	0x00,0x0c,0x12,0x20,0x20,0x20,0xfc,0x20,0x20,0x20,0x60,0xa0,0xb2,0x4c,0x00,0x00,
	0x00,0x82,0x82,0x44,0x28,0x10,0xfe,0x10,0x10,0xfe,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0xe0,0x90,0x88,0x88,0x88,0x94,0xe4,0x9f,0x84,0x84,0x84,0x84,0x84,0x00,0x00,
	0x00,0x0c,0x12,0x10,0x10,0x10,0xfe,0x10,0x10,0x10,0x10,0x10,0x90,0x60,0x00,0x00,
	0x0c,0x08,0x10,0x00,0x00,0x78,0x04,0x04,0x3c,0x44,0x84,0x84,0x44,0x3e,0x00,0x00,
	0x0c,0x08,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x0c,0x08,0x10,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x0c,0x08,0x10,0x00,0x00,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x42,0x3e,0x00,0x00,
	0x00,0x12,0x2a,0x24,0x00,0xf8,0x84,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x00,0x00,
	0x12,0x2a,0x24,0x00,0x82,0xc2,0xc2,0xa2,0x92,0x92,0x8a,0x86,0x86,0x82,0x00,0x00,
	0x00,0x00,0x00,0x78,0x04,0x04,0x3c,0x44,0x84,0x84,0x44,0x3e,0x00,0xfe,0x00,0x00,
	0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0xfe,0x00,0x00,
	0x00,0x10,0x10,0x00,0x00,0x10,0x10,0x20,0x44,0x82,0x82,0x82,0x44,0x38,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x80,0x80,0x80,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfe,0x02,0x02,0x02,0x00,0x00,
	0x00,0x10,0x30,0x10,0x10,0x10,0x00,0xfe,0x00,0x78,0x04,0x38,0x40,0x7c,0x00,0x00,
	0x00,0x10,0x30,0x10,0x10,0x10,0x00,0xfe,0x00,0x18,0x28,0x48,0x7c,0x08,0x00,0x00,
	0x00,0x10,0x10,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
	0x00,0x00,0x00,0x00,0x12,0x24,0x48,0x90,0x90,0x48,0x24,0x12,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x90,0x48,0x24,0x12,0x12,0x24,0x48,0x90,0x00,0x00,0x00,0x00,
	0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,0x11,0x44,
	0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,
	0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,0x77,0xdd,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x10,0xf0,0x10,0x10,0x10,0x10,0x10,0x10,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x10,0xf0,0x10,0x10,0x10,0x10,0x10,0x10,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x04,0xf4,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x04,0xf4,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf4,0x04,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x10,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x10,0x1f,0x10,0x10,0x10,0x10,0x10,0x10,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x10,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x10,0x17,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xf7,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x17,0x10,0x17,0x14,0x14,0x14,0x14,0x14,0x14,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x00,0xf7,0x14,0x14,0x14,0x14,0x14,0x14,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x00,0xff,0x10,0x10,0x10,0x10,0x10,0x10,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1f,0x10,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x10,0x1f,0x10,0x10,0x10,0x10,0x10,0x10,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x14,0x14,0x14,0x14,0x14,0x14,0x14,0xf7,0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xff,0x10,0xff,0x10,0x10,0x10,0x10,0x10,0x10,
	0x10,0x10,0x10,0x10,0x10,0x10,0x10,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,
	0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void vbe_set_color(uint32_t new_color);

void vbe_draw_string(const char *str, int scale, int x, int y);

void vbe_setup(struct vbe_mode_info *vbe_mode_info);