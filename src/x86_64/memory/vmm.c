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
    vmmblock = vmmStart; // start at the first address of the PDT reserved and mapped for that
    vmmblock->next = NULL; //vmmblock + SIZEOF_VMMBLOCK;
    vmmblock->used = false;
    vmmblock->page = vmmStart + SIZEOF_VMMBLOCK;
    curblock = vmmblock;
    curVmmAddr += PAGE_SIZE;
}

virtaddr allocate_page(uint size)
{
    uint block = (size / PAGE_SIZE) + 0x1;
    uint keep = block;
    struct vmmblock *vmm  = vmmblock;

    for (; block == 0x1 && vmm; vmm = vmm->next)
        if (!vmm->used)
            return (vmm + SIZEOF_VMMBLOCK);
    vmm = curblock;
    for (; block != 0x0; block--) {
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
        curblock = curblock->next;
    }
    return (vmm->page);
}

void free_page(virtaddr rect)
{
    uint involved;

    struct vmmblock *vmm = vmmblock;
    for (; vmm; vmm = vmm->next)
        if (vmm + SIZEOF_VMMBLOCK == rect) {
            involved = vmm->involved;
            for (; vmm && involved > 0x0; vmm = vmm->next, involved--)
                vmmblock->used = false;
            return;
        }
    PANIC("Invalid pointer in free_page\n");
}

// void mmap(physaddr frame, virtaddr page)
// {
//
// }
