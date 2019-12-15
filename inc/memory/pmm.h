#ifndef _PMM_H
#define _PMM_H

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

/* A Phys PageFrame sizeof 0x1000 */
struct PageFrame
{
    /* Next PageFrame */
    struct PageFrame *next;
    /* Pointer on the first Block/flag managing internal Phys PageFrame memory */
    struct Block     *firstblock;
    uint             free_mm;
};

/* Block Memory */
struct Block
{
    struct Block *next;
    uint size;
    bool used;
};

#define SIZEOF_PHYS_BLOCK       sizeof(struct Block)

#define SIZEOF_FLAG_PAGE_FRAME  sizeof(struct PageFrame)
#define SIZEOF_PAGE_FRAME       PAGE_SIZE

void alloc_first_page(void);
struct PageFrame *alloc_page(void);
void *phys_allok(uint64 size);
void init_pmm(uint64 size);
void phys_kfree(void *free);

#endif
