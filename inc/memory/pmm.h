#ifndef _PMM_H
#define _PMM_H

#include "eternity.h"
#include "sysdef.h"
#include "memory.h"

#define BLOCK_SIZE  0x1000

/* this is the total hardcode pmm available */
#define PMM_SIZE    ((uint64)M * BLOCK_SIZE)

/* bitmap chirurgical operation */
#define SETBITMAP(addr)   (bitmapManager[addr] |= (1 << (addr % BLOCK_SIZE)))
#define CLEARBITMAP(addr) (bitmapManager[addr] &= (~(1 << (addr % BLOCK_SIZE))))
#define BITSTATE(addr)    ((bitmapManager[addr] >> (addr % BLOCK_SIZE)) & 0x1)

/* aligne block address */
#define ALIGN_BLOCK(addr) (((addr) & (MAX_ADDR_64B_SYS - (BLOCK_SIZE - 0x1))) + 0x1000)

/* Physical memory types */
enum PMM_TYPE
{
    PMM_TYPE_USABLE   = 0x1,   /* Reported usable by the BIOS */
    PMM_TYPE_RESERVED = 0x2,   /* Reported (or inferred) to be reserved */
    PMM_TYPE_ACPI     = 0x3,   /* Used for ACPI tables or code */
    PMM_TYPE_ACPI_NVS = 0x4,   /* Used for ACPI non-volatile storage */
    PMM_TYPE_BAD      = 0x5,   /* Reported as bad memory */
    PMM_TYPE_UNCACHED = 0x6,   /* Marked as uncacheable, usually for I/O */
    PMM_TYPE_UNMAPPED = 0x7,   /* Marked as "do not map" */
};

void *frame_allocator(uint64 size);
uint64 allocate_consecutive_frame(uint nbr);
uint64 allocate_frame(void);
uint64 find_free_frame(void);
uint64 find_consecutive_free_frame(uint frameNbr);
void free_frame(uint64 block);
void free_consecutive_frame(uint64 block);
void init_pmm(uint64 size);

#endif