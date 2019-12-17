#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"

/* page define at boot are accessed with translation */
#define V2P(x) ((uint64)x - (uint64)(&__KERNEL_VIRT_BASE))
#define P2V(x) ((uint64)x + (uint64)(&__KERNEL_VIRT_BASE))

#define PAGE_ADDR_BITSIZE 0x9
#define PML4_ADDR_INDEX   0x27
#define PML4_ENTRY_INDEX(x) ((x >> PML4_ADDR_INDEX) & ((0x1 << PAGE_ADDR_BITSIZE) - 0x1))
#define PDPT_ADDR_INDEX   0x1E
#define PDPT_ENTRY_INDEX(x) ((x >> PDPT_ADDR_INDEX) & ((0x1 << PAGE_ADDR_BITSIZE) - 0x1))

#define PAGE_ENTRY_NBR 0x200

struct pageTable {
    uint64 pml4[PAGE_ENTRY_NBR];
    uint64 pdpt[PAGE_ENTRY_NBR];
    uint64 pdt_kernel_static[PAGE_ENTRY_NBR];
    uint64 pdt_kernel_dynamic[PAGE_ENTRY_NBR];
    uint64 pdt_user[PAGE_ENTRY_NBR];
};

struct pageTable *kernelPageTable;

/* VIRTUAL PAGE BITS SETTINGS */
enum pageAttrib {
    PRESENT             = 0x1,    // page is mapped to physical address
    WRITABLE            = 0x2,    // page can be read/written
    USER_ACCESSIBLE     = 0x4,    // page can be accessed from protection ring 3 (user space)
    HUGE_PAGE           = 0x80,   // page is 2MB (if used in pde) or 1GB (if used in pdpt) instead of standard 4096 bytes
    GLOBAL_PAGE         = 0x100,  // page is shared across processes (useful for kernel pages)
    STACK_GUARD_PAGE    = 0x200,  // page is a stack guard; together with "non present" allows for detection of stack overflows
};

void HVMmapping(void);

#endif
