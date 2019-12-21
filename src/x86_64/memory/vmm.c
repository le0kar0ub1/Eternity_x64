#include "vmm.h"
#include "paging.h"
#include "pmm.h"

/* start a the end of kernel phys */
virtaddr managerVmmStart;
virtaddr vmmStart;

virtaddr curVmmAddr;

struct vmmblock *vmmblock;
struct vmmblock *curblock;

extern struct pageTable *kpage; // mmap working needed

void dump_kpage(void)
{
    for (struct vmmblock *vmm = vmmblock; vmm; vmm = vmm->next)
        kprint("Page at address: %x, used: %d", vmm->page, vmm->used);
}

virtaddr kmem_request(uint size)
{
    virtaddr page = allocate_page(size);
    physaddr frame = frame_allocator(size);
    mmap(page, frame, ALIGN_BLOCK(size));
    return (page);
}

void init_vmm(void)
{
    vmmblock = fromIndexToAdrr(KERNEL_PML4_ENTRY, KERNEL_PDPT_ENTRY, 0x1, 0x0);
    vmmStart = fromIndexToAdrr(KERNEL_PML4_ENTRY, KERNEL_PDPT_ENTRY, 0x2, 0x0);
    mmap(vmmStart, frame_allocator(PAGE_SIZE), PAGE_SIZE);
    mmap(vmmblock, frame_allocator(PAGE_SIZE), PAGE_SIZE);
    vmmblock->next = NULL;
    vmmblock->used = false;
    vmmblock->page = vmmStart + SIZEOF_VMMBLOCK;
    curblock = vmmblock;
    curVmmAddr = vmmStart + PAGE_SIZE;
}

virtaddr allocate_page(uint size)
{
    uint block = !(size % PAGE_SIZE) ? (size / PAGE_SIZE) : ((size / PAGE_SIZE) + 0x1);
    uint keep = block;
    struct vmmblock *vmm = vmmblock;

    for (; block == 0x1 && vmm; vmm = vmm->next)
        if (!vmm->used) {
            vmm->used = true;
            return (vmm->page);
        }
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

void mmap(virtaddr virt, physaddr phys, uint off)
{
    uint pd = PD_INDEX(virt) - 0x1;
    uint pt = PT_INDEX(virt);
    off /= PAGE_SIZE;
    for (; off > 0x0 && pt < PAGE_ENTRY_NBR;) {
        kpage->pt_kernel_dynamic[pd][pt] = phys | PRESENT | WRITABLE;
        pt += 0x1;
        phys += PAGE_SIZE;
        off -= 0x1;
    }
}
