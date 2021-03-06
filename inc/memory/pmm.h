#ifndef _PMM_H
#define _PMM_H

#include "eternity.h"
#include "sysdef.h"
#include "memory.h"

/* this is the total hardcode pmm available */
#define PMM_SIZE    ((uint64)M * FRAME_SIZE)
#define BITMAP_SIZE (PMM_SIZE / FRAME_SIZE)

/* bitmap chirurgical operation */
// #define SETBITMAP(addr)   (bitmap[addr] |= (1 << (addr % FRAME_SIZE)))
// #define CLEARBITMAP(addr) (bitmap[addr] &= (~(1 << (addr % FRAME_SIZE))))
// #define BITSTATE(addr)    ((bitmap[addr] >> (addr % FRAME_SIZE)) & 0x1)

#define SETBITMAP(x, v) (bitmap[x] = v)
#define CLEARBITMAP(x)  (bitmap[x] = 0x0)
#define BITSTATE(x)     (bitmap[x])

/* aligne block address */
// #define ALIGN_BLOCK(addr) (((addr) & (MAX_ADDR_64B_SYS - (FRAME_SIZE - 0x1))) + 0x1000)

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

physaddr_t frame_allocator(uint64);
physaddr_t allocate_frame(uint);
uint64 find_free_frame(uint);
void free_frame(uint64);
void init_pmm(void);

#endif
