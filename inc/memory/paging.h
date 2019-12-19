#ifndef _PAGING_H_
#define _PAGING_H_

#include "memory.h"

#define PML4_INDEX(x) ((((uint64)(x)) >> 0x27) & (PAGE_ENTRY_NBR - 0x1))
#define PDPT_INDEX(x) ((((uint64)(x)) >> 0x1E) & (PAGE_ENTRY_NBR - 0x1))
#define PD_INDEX(x)   ((((uint64)(x)) >> 0x15) & (PAGE_ENTRY_NBR - 0x1))
#define PT_INDEX(x)   ((((uint64)(x)) >> 0x0C) & (PAGE_ENTRY_NBR - 0x1))

#define PAGE_ENTRY_NBR  0x200

#define TWOMIB_PAGESIZE  0x200000
#define FOURKIB_PAGESIZE 0x1000

struct pageTable {
    uint64 pml4[PAGE_ENTRY_NBR];
    uint64 pdpt[PAGE_ENTRY_NBR];
    uint64 pdt[PAGE_ENTRY_NBR];
    uint64 pt_kernel_static[PAGE_ENTRY_NBR];
    uint64 pt_kernel_dynamic[PAGE_ENTRY_NBR];
    uint64 pt_user[PAGE_ENTRY_NBR];
};

struct pageTable *kernelPage;

/* VIRTUAL PAGE BITS SETTINGS */
enum pageAttrib {
    PRESENT          = 0x1,   // page is mapped to physical address
    WRITABLE         = 0x2,   // page can be read/written
    USER_ACCESSIBLE  = 0x4,   // page can be accessed from protection ring 3 (user space)
    HUGE_PAGE        = 0x80,  // page is 2MB (if used in pde) or 1GB (if used in pdpt) instead of standard 4096 bytes
    GLOBAL_PAGE      = 0x100, // page is shared across processes (useful for kernel pages)
    STACK_GUARD_PAGE = 0x200, // page is a stack guard; together with "non present" allows for detection of stack overflows
};

void kernelMapping(void);

#endif
