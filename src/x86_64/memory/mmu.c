#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "pagedef.h"
#include "ports.h"

/* define in linker script */
extern uint64 __KERNEL_VIRT_LINK;

/* from PMM */
extern uint8 *bitmap;

/* from mem boostrap */
extern virtaddr_t boostrap;

pml4_t *kpml4;

// void mmap(virtaddr_t page, physaddr_t frame)
// {
//     // uint read_cr3();
// }

// void switch_pml4(pml4_t *page)
// {

// }

void init_paging(void)
{
    /* init the boostrap allocator */
    boostrap = (virtaddr_t)ALIGN_PAGE(((uint64)bitmap + BITMAP_SIZE));
    kpml4 = (pml4_t *)boostrap_kalloc(sizeof(pml4_t));
    memset(kpml4, 0x0, sizeof(pml4_t));

    /* mapp static kernel */
    uint64 mapp = ((uint64)&__KERNEL_VIRT_LINK);
    while (mapp < ((uint64)&__KERNEL_VIRT_LINK) + (6 * M)) {
        boostrap_allocate_page(kpml4, (virtaddr_t)mapp, PRESENT | WRITABLE | GLOBAL_PAGE | USER_ACCESSIBLE);
        mapp += PAGE_SIZE;
    }
    write_cr3(V2P(kpml4));
    serial_kprint("OUT OF MAPPING\n");
    while (1);
}