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
void boostrap_allocate_page(pml4_t *root, virtaddr_t virt, uint32 flag)
{
    fatalAssert(root);
    /* address index */
    uint16 index_pml4 = PML4_INDEX(virt);
    uint16 index_pdpt = PDPT_INDEX(virt);
    uint16 index_pd   = PD_INDEX(virt);
    uint16 index_pt   = PT_INDEX(virt);

    pdpt_t *pdptExistence = root->ref[index_pml4];
    if (!pdptExistence) {
        pdptExistence = boostrap_kalloc(sizeof(pdpt_t));
        memset(pdptExistence, 0x0, sizeof(pdpt_t));
        root->entry[index_pml4].frame      = V2P(pdptExistence);
        root->entry[index_pml4].present    = (flag & PRESENT) > 0x0 ? 0x1 : 0x0;
        root->entry[index_pml4].rw         = (flag & WRITABLE) > 0x0 ? 0x1 : 0x0;
        root->entry[index_pml4].supervisor = (flag & USER_ACCESSIBLE) > 0x0 ? 0x1 : 0x0;
        // root->entry[index_pml4].pagesize   = (flag & HUGE_PAGE) > 0x0 ? 0x1 : 0x0;
        root->ref[index_pml4] = pdptExistence;
    }

    pd_t *pdExistence = pdptExistence->ref[index_pdpt];
    if (!pdExistence) {
        pdExistence = boostrap_kalloc(sizeof(pd_t));
        memset(pdExistence, 0x0, sizeof(pd_t));
        pdptExistence->entry[index_pdpt].frame      = V2P(pdExistence);
        pdptExistence->entry[index_pdpt].present    = (flag & PRESENT) > 0x0 ? 0x1 : 0x0;
        pdptExistence->entry[index_pdpt].rw         = (flag & WRITABLE) > 0x0 ? 0x1 : 0x0;
        pdptExistence->entry[index_pdpt].supervisor = (flag & USER_ACCESSIBLE) > 0x0 ? 0x1 : 0x0;
        // pdptExistence->entry[index_pdpt].pagesize   = (flag & HUGE_PAGE) > 0x0 ? 0x1 : 0x0;
        pdptExistence->ref[index_pdpt] = pdExistence;
    }

    pt_t *ptExistence = pdExistence->ref[index_pd];
    if (!ptExistence) {
        ptExistence = boostrap_kalloc(sizeof(pt_t));
        memset(ptExistence, 0x0, sizeof(pt_t));
        pdExistence->entry[index_pd].frame      = V2P(ptExistence);
        pdExistence->entry[index_pd].present    = (flag & PRESENT) > 0x0 ? 0x1 : 0x0;
        pdExistence->entry[index_pd].rw         = (flag & WRITABLE) > 0x0 ? 0x1 : 0x0;
        pdExistence->entry[index_pd].supervisor = (flag & USER_ACCESSIBLE) > 0x0 ? 0x1 : 0x0;
        // pdExistence->entry[index_pd].pagesize   = (flag & HUGE_PAGE) > 0x0 ? 0x1 : 0x0;
        pdExistence->ref[index_pd] = ptExistence;
    }

    pt_entry_t *page = &(ptExistence->page[index_pt]);
    if (!page->present) {
        page->frame      = frame_allocator(FRAME_SIZE);
        page->present    = (flag & PRESENT) > 0x0 ? 0x1 : 0x0;
        page->rw         = (flag & WRITABLE) > 0x0 ? 0x1 : 0x0;
        page->supervisor = (flag & USER_ACCESSIBLE) > 0x0 ? 0x1 : 0x0;
    }
}