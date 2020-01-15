#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "pagedef.h"
#include "ports.h"

/* from PMM */
extern uint8 *bitmap;

/* from mem boostrap */
extern virtaddr_t boostrap;

pml4_t *kpml4;

// void mmap(virtaddr_t page, physaddr_t frame, int flags)
// {
//     pml4_t *root = (pml4_t *)read_cr3();
//     assert_ne((uint64)root, 0x0);
// }

uintptr virtToPhys(virtaddr_t virt)
{
    pml4_t *root = (pml4_t *)read_cr3();
    assert_ne((uint64)root, 0x0);

    /* address index */
    uint16 index_pml4 = PML4_INDEX(virt);
    uint16 index_pdpt = PDPT_INDEX(virt);
    uint16 index_pd   = PD_INDEX(virt);
    uint16 index_pt   = PT_INDEX(virt);

    pdpt_t *pdpt = root->ref[index_pml4];
    assert_ne((uint64)pdpt, 0x0);
    pd_t *pd  = pdpt->ref[index_pdpt];
    assert_ne((uint64)pd, 0x0);
    pt_t *pt = pd->ref[index_pd];
    assert_ne((uint64)pt, 0x0);
    uintptr phys = pt->page[index_pt].frame;
    return (phys);
}

void switch_pml4(pml4_t *page)
{
    uintptr phys = virtToPhys(page);
    write_cr3(phys);
}

void init_paging(void)
{
    /* init the boostrap allocator */
    boostrap = (virtaddr_t)ALIGN_PAGE(((uint64)bitmap + BITMAP_SIZE));
    serial_kprint("Alloc Phys: %x Virt: %x\n", V2P(boostrap), (uint64)boostrap);
    serial_kprint("PHYS: %x -> %x\n", (&__KERNEL_PHYS_START), (&__KERNEL_PHYS_END));
    serial_kprint("VIRT: %x -> %x\n", (&__KERNEL_VIRT_LINK), (&__KERNEL_VIRT_END));
    kpml4 = (pml4_t *)boostrap_kalloc(sizeof(pml4_t));
    memset(kpml4, 0x0, sizeof(pml4_t));

    /* mapp static kernel */
    uint64 mapp = ((uint64)KERN_VIRT_BASE);
    uint32 pageFlags = PRESENT | WRITABLE | GLOBAL_PAGE | USER_ACCESSIBLE;
    while (mapp < ((uint64)KERN_VIRT_BASE) + (0x10 * M)) {
        boostrap_allocate_page(kpml4, (virtaddr_t)mapp, pageFlags);
        mapp += PAGE_SIZE;
    }
    write_cr3(V2P(((uint64)(kpml4))));
    while (1);
    // serial_kprint("OUT OF MAPPING\n");
}