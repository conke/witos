#pragma once

#include <types.h>
#include <list.h>
#include <device.h>

typedef enum
{
	PT_NONE,
	PT_BAD,
	PT_FREE,
	PT_BL_GTH,
	PT_BL_GBH,
	PT_BL_GCONF,
	PT_BL_UBOOT,
	PT_OS_LINUX,
	PT_OS_WINCE,
	PT_FS_RAMDISK,
	PT_FS_CRAMFS,
	PT_FS_BEGIN = PT_FS_CRAMFS,
	PT_FS_JFFS2,
	PT_FS_YAFFS,
	PT_FS_YAFFS2,
	PT_FS_UBIFS,
	PT_FS_END = PT_FS_UBIFS
} PART_TYPE;

#define PART_NAME_LEN 32

struct part_attr
{
	PART_TYPE part_type;
	u32   part_base;
	u32   part_size;
	char  part_name[PART_NAME_LEN];
};

struct block_device
{
	struct device dev;

	size_t bdev_base;
	size_t bdev_size;
	size_t sect_size;

	// struct fat_fs *fs;
	void *fs; // fixme
	struct list_node bdev_node;
};

int block_device_register(struct block_device *bdev);

struct block_device *get_bdev_by_name(const char *name);
