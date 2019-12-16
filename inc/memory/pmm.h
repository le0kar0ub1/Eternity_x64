#ifndef _PMM_H
#define _PMM_H

#include "eternity.h"

#define BLOCK_SIZE  0x1000
#define BLOCK_GROUP 0x8

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

void alloc_first_page(void);
struct PageFrame *alloc_page(void);
void *phys_allok(uint64 size);
void init_pmm(uint64 size);
void phys_kfree(void *free);

#endif
