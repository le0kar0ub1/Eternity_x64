#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "pagedef.h"

extern uint8 *bitmap;

/* from mem boostrap */
extern virtaddr_t boostrap;

pml4_t *kpml4;

void init_paging(void)
{
    /* init the boostrap allocator */
    boostrap = (virtaddr_t)ALIGN_PAGE(((uint64)bitmap + BITMAP_SIZE));
    kpml4 = (pml4_t *)dumb_kalloc(sizeof(pml4_t));
    memset(kpml4, 0x0, sizeof(pml4_t));

    /* mapp static kernel */
    // kpml4->entry

    while (1);
}