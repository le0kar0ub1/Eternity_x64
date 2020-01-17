#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "pagedef.h"
#include "ports.h"

void mmap(virtaddr_t virt, physaddr_t frame, int flag)
{
    pml4_t *root = (pml4_t *)read_cr3();
    assert_ne((uint64)root, 0x0);

    /* address index */
    uint16 index_pml4 = PML4_INDEX(virt);
    uint16 index_pdpt = PDPT_INDEX(virt);
    uint16 index_pd   = PD_INDEX(virt);
    uint16 index_pt   = PT_INDEX(virt);

    pdpt_t *pdptExistence = root->ref[index_pml4];
    if (!pdptExistence) {
        pdptExistence = kalloc(sizeof(pdpt_t));
        memset(pdptExistence, 0x0, sizeof(pdpt_t));
        root->entry[index_pml4].frame      = virtToPhys(pdptExistence) >> 12;
        root->entry[index_pml4].present    = (flag & PRESENT) > 0 ? 1 : 0;
        root->entry[index_pml4].rw         = (flag & WRITABLE) > 0 ? 1 : 0;
        root->entry[index_pml4].supervisor = (flag & USER_ACCESSIBLE) > 0 ? 1 : 0;
        root->entry[index_pml4].global     = (flag & GLOBAL_PAGE) > 0 ? 1 : 0;
        // root->entry[index_pml4].pagesize   = (flag & HUGE_PAGE) > 0 ? 1 : 0;
        root->ref[index_pml4] = pdptExistence;
    }

    pd_t *pdExistence = pdptExistence->ref[index_pdpt];
    if (!pdExistence) {
        pdExistence = kalloc(sizeof(pd_t));
        memset(pdExistence, 0x0, sizeof(pd_t));
        pdptExistence->entry[index_pdpt].frame      = virtToPhys(pdExistence) >> 12;
        pdptExistence->entry[index_pdpt].present    = (flag & PRESENT) > 0 ? 1 : 0;
        pdptExistence->entry[index_pdpt].rw         = (flag & WRITABLE) > 0 ? 1 : 0;
        pdptExistence->entry[index_pdpt].supervisor = (flag & USER_ACCESSIBLE) > 0 ? 1 : 0;
        pdptExistence->entry[index_pdpt].global     = (flag & GLOBAL_PAGE) > 0 ? 1 : 0;
        // pdptExistence->entry[index_pdpt].pagesize   = (flag & HUGE_PAGE) > 0 ? 1 : 0;
        pdptExistence->ref[index_pdpt] = pdExistence;
    }

    pt_t *ptExistence = pdExistence->ref[index_pd];
    if (!ptExistence) {
        ptExistence = kalloc(sizeof(pt_t));
        memset(ptExistence, 0x0, sizeof(pt_t));
        pdExistence->entry[index_pd].frame      = virtToPhys(ptExistence) >> 12;
        pdExistence->entry[index_pd].present    = (flag & PRESENT) > 0 ? 1 : 0;
        pdExistence->entry[index_pd].rw         = (flag & WRITABLE) > 0 ? 1 : 0;
        pdExistence->entry[index_pd].supervisor = (flag & USER_ACCESSIBLE) > 0 ? 1 : 0;
        pdExistence->entry[index_pd].global     = (flag & GLOBAL_PAGE) > 0 ? 1 : 0;
        // pdExistence->entry[index_pd].pagesize   = (flag & HUGE_PAGE) > 0 ? 1 : 0;
        pdExistence->ref[index_pd] = ptExistence;
    }

    pt_entry_t *page = &(ptExistence->page[index_pt]);
    if (!page->present) {
        page->frame      = frame >> 12;
        page->present    = (flag & PRESENT) > 0 ? 1 : 0;
        page->rw         = (flag & WRITABLE) > 0 ? 1 : 0;
        page->supervisor = (flag & USER_ACCESSIBLE) > 0 ? 1 : 0;
        page->global     = (flag & GLOBAL_PAGE) > 0 ? 1 : 0;
    } else {
        PANIC("Mmap failed, address %x already mapped\n", virt);
    }
}

void allocate_segment(pml4_t *root, virtaddr_t start, virtaddr_t end, uint flag)
{
    /* clean up useless part */
    start = (virtaddr_t)((uint64)start & (uint64)(MAX_ADDR_64B_SYS - (PAGE_SIZE - 0x1)));
    end   = (virtaddr_t)((uint64)start & (uint64)(MAX_ADDR_64B_SYS - (PAGE_SIZE - 0x1)));
    while (start <= end) {
        allocate_page(root, start, flag);
        start += PAGE_SIZE;
    }
}

void free_segment(virtaddr_t start, virtaddr_t end)
{
    /* clean up useless part */
    start = (virtaddr_t)((uint64)start & (uint64)(MAX_ADDR_64B_SYS - (PAGE_SIZE - 0x1)));
    end   = (virtaddr_t)((uint64)start & (uint64)(MAX_ADDR_64B_SYS - (PAGE_SIZE - 0x1)));
    while (start <= end) {
        free_page(start);
        start += PAGE_SIZE;
    }
}
