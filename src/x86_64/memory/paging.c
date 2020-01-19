#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "pagedef.h"
#include "ports.h"
#include "threads.h"

/* from PMM */
extern uint8 *bitmap;

/* from mem boostrap */
extern virtaddr_t boostrap;

pml4_t *kpml4;

void *fromIndexToAdrr(uint64 pml4, uint64 pdpt, uint64 pdt, uint64 pt)
{
    uint64 addr;

    addr = (((0x1 << 0x9) - (0x1 << 0x8)) & pml4) > 0x0 ? 0xffff000000000000 : 0x0;
    addr += pml4 << 0x27;
    addr += pdpt << 0x1E;
    addr += pdt  << 0x15;
    addr += pt   << 0x0C;
    return ((void *)addr);
}

bool isPageAlreadyMapped(pml4_t *root, virtaddr_t *virt)
{
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
    bool ismapped = pt->page[index_pt].present;
    return (ismapped);
}

uintptr virtToPhys(pml4_t *root, virtaddr_t virt)
{
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
    uintptr phys = (pt->page[index_pt].frame << 12) + PAGE_OFFSET(virt);
    return (phys);
}

void switch_pml4(pml4_t *root, pml4_t *new)
{
    uintptr phys = virtToPhys(root, new);
    write_cr3(phys);
}

void heap_reserved(pml4_t *root)
{
    uint64 mapp = KHEAP_BASE_START;
    uint32 pageFlags = PRESENT | WRITABLE | GLOBAL_PAGE | USER_ACCESSIBLE;

    /* mapp the kheap not aligned */
    while (mapp < ((uint64)KHEAP_BASE_START) + KHEAP_BASE_SIZE) {
        boostrap_allocate_page(root, (virtaddr_t)mapp, pageFlags);
        mapp += PAGE_SIZE;
    }
    /* mapp a system memory which will be used full aligned */
    mapp = SYSTEM_HEAP_BASE_START;
    while (mapp < ((uint64)SYSTEM_HEAP_BASE_START) + SYSTEM_HEAP_BASE_SIZE) {
        boostrap_allocate_page(root, (virtaddr_t)mapp, pageFlags);
        mapp += PAGE_SIZE;
    }
}

void init_paging(void)
{
    /* init the boostrap allocator */
    boostrap = (virtaddr_t)ALIGN_PAGE(((uint64)bitmap + BITMAP_SIZE));
    kpml4 = (pml4_t *)ALIGN_PAGE((uint64)boostrap_kalloc(sizeof(pml4_t)));
    memset(kpml4, 0x0, sizeof(pml4_t));

    /* mapp static kernel */
    uint64 mapp = ((uint64)KERN_VIRT_BASE);
    uint32 pageFlags = PRESENT | WRITABLE | GLOBAL_PAGE | USER_ACCESSIBLE;
    /* static kernel memory */
    while (mapp < ((uint64)KERN_VIRT_BASE) + BOOSTRAP_MEMORY_SIZE) {
        boostrap_allocate_page(kpml4, (virtaddr_t)mapp, pageFlags);
        mapp += PAGE_SIZE;
    }
    heap_reserved(kpml4);
    write_cr3(V2P((uint64)(kpml4)));
}

void pageFault_handler(struct frame *frame)
{
    /* Page faults in kernel space leads to death */
     uint64 fault_addr = read_cr2(); /* read cr2 to get faulting address */

     vga_set_attrib(VGA_RED, VGA_BLACK);
     kprint("Page Fault at address : %x\n", fault_addr);
     /* error num pushed by CPU give info on page fault */
     if (!(frame->error & ERR_PF_PRES))
         kprint("No present in memory\n");
     if ((frame->error & ERR_PF_RW))
         kprint("Page is read only\n");
     if ((frame->error & ERR_PF_USER))
         kprint("Kernel page access\n");
     if (frame->error & ERR_PF_RES)
         kprint("Overwritten CPU-reserved bits of page entry\n");
     if (frame->error & ERR_PF_INST)
         kprint("Instruction fetch\n");
    cpuContextDump((struct cpuContext *)frame);
    vga_set_attrib(VGA_WHITE, VGA_BLACK);
    serial_kprint("Faulting address: %x\n", frame->rip);
    hlt();
}

void init_pf_handler(void)
{
    register_int_handler(INT_PAGE_FAULT, pageFault_handler);
}