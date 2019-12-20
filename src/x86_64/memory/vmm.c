#include "vmm.h"
#include "paging.h"
#include "pmm.h"

/* start a the end of kernel phys */
virtaddr managerVmmStart;
virtaddr vmmStart;

virtaddr curVmmAddr;

struct vmmblock *vmmblock;
struct vmmblock *curblock;

void init_vmm(void)
{
    managerVmmStart = fromIndexToAdrr(KERNEL_PML4_ENTRY, KERNEL_PDPT_ENTRY, KERNEL_MEMMANAGE_PDT_ENTRY, 0x0);
    vmmStart = fromIndexToAdrr(KERNEL_PML4_ENTRY, KERNEL_PDPT_ENTRY, KERNEL_DYNAMIC_PDT_ENTRY, 0x0);
    vmmblock = managerVmmStart; // start at the first address of the PDT reserved and mapped for that
    vmmblock->next = NULL; //vmmblock + SIZEOF_VMMBLOCK;
    vmmblock->used = false;
    vmmblock->page = vmmStart;
    curblock = vmmblock;
    curVmmAddr += PAGE_SIZE;
}

void memRequest(uint size)
{
    uint block = (size / PAGE_SIZE) + 0x1;

    for (uint keep = block; block != 0x0; block--) {
        curblock->next = SIZEOF_VMMBLOCK + curblock;
        curblock->page = curVmmAddr;
        if (keep == block && keep > 0x1)
            curblock->involved = keep;
        else if (keep > 0x1)
            curblock->involved = 0x0;
        else
            curblock->involved = 0x1;
        curblock->used = true;
        curVmmAddr += 0x1000;
    }
}

// void mmap(physaddr frame, virtaddr page)
// {
//
// }

// void request_page(uint size)
// {
//     physaddr = frame_allocator(size);
//     cur =
// }
