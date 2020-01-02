#include "vmm.h"
#include "paging.h"
#include "pmm.h"

/* start a the end of kernel phys */
virtaddr_t managerVmmStart;
virtaddr_t vmmStart;

virtaddr_t curVmmAddr;

struct vmmblock *vmmblock;
struct vmmblock *curblock;

extern struct pageTable *kpage; // mmap working needed

uint64 cycleManagerPage;
uint64 managerPageNumber;

void dump_kpage(void)
{
    for (struct vmmblock *vmm = vmmblock; vmm; vmm = vmm->next)
        kprint("Page at address: %x, used: %d", vmm->page, vmm->used);
}

virtaddr_t kmem_request(uint size)
{
    virtaddr_t page = allocate_page(size);
    physaddr_t frame = frame_allocator(size);
    mmap(page, frame, ALIGN_PAGE(size));
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
    vmmblock->involved = 0x1;
    vmmblock->page = vmmStart + SIZEOF_VMMBLOCK;
    curblock = vmmblock;
    curVmmAddr = vmmStart + PAGE_SIZE;
    cycleManagerPage = 0x1;
    managerPageNumber = 0x1;
}

void newManagerSpace(void)
{
    cycleManagerPage = 0x0;
    mmap(vmmblock + (managerPageNumber * PAGE_SIZE), frame_allocator(PAGE_SIZE), PAGE_SIZE);
    managerPageNumber += 0x1;
}

virtaddr_t allocate_page(uint size)
{
    uint block = !(size % PAGE_SIZE) ? (size / PAGE_SIZE) : ((size / PAGE_SIZE) + 0x1);
    uint keep = block;
    struct vmmblock *vmm = vmmblock;

    /* if free page exist */
    for (; vmm; vmm = vmm->next) {
        if (!vmm->used && vmm->involved == block) {
            vmm->used = true;
            return (vmm->page);
        }
    }
    /* check if we need a new page to manage page X) */
    if (cycleManagerPage + block + 1 > PAGE_SIZE / SIZEOF_VMMBLOCK)
        newManagerSpace();
    vmm = curblock;
    /* else allocate new page */
    for (; block != 0x0; block--) {
        curblock->next = (struct vmmblock *)((uint64)SIZEOF_VMMBLOCK + (uint64)curblock);
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
    cycleManagerPage += block;
    return (vmm->page);
}

void free_page(virtaddr_t rect)
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

void mmap(virtaddr_t virt, physaddr_t phys, uint off)
{
    uint pd = PD_INDEX(virt) - 0x1;
    uint pt = PT_INDEX(virt);
    off /= PAGE_SIZE;
    for (; off > 0x0 && pt < PAGE_ENTRY_NBR;) {
        kpage->pt_kernel_dynamic[pd][pt] = phys | PRESENT | WRITABLE | USER_ACCESSIBLE;
        pt += 0x1;
        phys += PAGE_SIZE;
        off -= 0x1;
    }
}
