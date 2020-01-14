#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "memory.h"
#include "ports.h"

virtaddr_t boostrap = 0x0;

/* Used to boostrap the MMU */
virtaddr_t boostrap_kalloc(uint64 size)
{
    /* bcs its used to boostrap the mmu, address are always aligned on page size */
    /* btw we will secure it */
    if (!IS_PAGE_ALIGNED(size))
        size = ALIGN_PAGE(size);
    boostrap = (virtaddr_t)((uint64)boostrap + size);
    return ((virtaddr_t)((uint64)boostrap - size));
}

/* Used to boostrap the MMU */
virtaddr_t boostrap_allocate_page(pml4_t *root, virtaddr_t virt, uint32 flag)
{
    fatalAssert(root);
    /* address index */
    uint16 index_pml4 = PML4_INDEX(virt);
    uint16 index_pdpt = PDPT_INDEX(virt);
    uint16 index_pd   = PD_INDEX(virt);
    uint16 index_pt   = PT_INDEX(virt);

    pdpt_t *existence = root->ref[index_pml4];
    if (!root->ref[index_pml4]) {
        existence = boostrap_kalloc(sizeof(pdpt_t));
        memset(existence, 0x0, sizeof(pdpt_t));
        root->entry[index_pml4].frame      = V2P(existence);
        root->entry[index_pml4].present    = flag & PRESENT;
        root->entry[index_pml4].rw         = flag & WRITABLE;
        root->entry[index_pml4].supervisor = flag & USER_ACCESSIBLE;
        root->entry[index_pml4].pagesize   = flag & HUGE_PAGE;
        root->ref[index_pml4] = existence;
    }
    while (1);
    return (NULL);
}