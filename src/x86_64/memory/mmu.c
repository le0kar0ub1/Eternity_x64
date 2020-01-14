#include "paging.h"
#include "vmm.h"

virtaddr_t dumbMem = 0x0;

/* Used to boostrap the MMU */
virtaddr_t dumb_kalloc(uint64 size)
{
    /* bcs its used to boostrap the mmu, address are always aligned on page size */
    /* btw we will secure it */
    if (!IS_PAGE_ALIGNED(size))
        size = ALIGN_PAGE(size);
    dumbMem = (virtaddr_t)((uint64)dumbMem + size);
    return ((virtaddr_t)((uint64)dumbMem - size));
}

void init_paging(void)
{
    
}