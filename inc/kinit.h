#ifndef _KINIT_H_
#define _KINIT_H_

/* INIT LEVEL */
enum init_level
{
	INIT_LEVEL_EARLIEST		= 0x1,

	INIT_LEVEL_MULTIBOOT,

	INIT_LEVEL_MMU,

	INIT_LEVEL_ARCH,

	INIT_LEVEL_DRIVERS,

	INIT_LEVEL_LATEST,
};

#endif