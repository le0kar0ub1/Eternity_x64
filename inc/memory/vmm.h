#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

#define BOOSTRAP_MEMORY_SIZE (0x4 * M)
#define KHEAP_BASE_START ((uint64)KERN_VIRT_BASE + BOOSTRAP_MEMORY_SIZE)
#define KHEAP_BASE_SIZE (2 * M)
#define KHEAP_BASE_END (KHEAP_BASE_START + KHEAP_BASE_SIZE)

#define BOOSTRAP_MEM_END (BOOSTRAP_MEMORY_SIZE + KHEAP_BASE_SIZE + (uint64)KERN_VIRT_BASE)

#endif
