#include "eternity.h"
#include "paging.h"
#include "pmm.h"
#include "memory.h"

extern uint64 PML4;
extern uint64 PDPT;
extern uint64 PDT;

extern uint64 __KERNEL_VIRT_SIZE;

struct pageTable *kernelPage;

void init_kpaging(void)
{
    kernelPage = (struct pageTable *)ALIGN_BLOCK((uint64)kernelPage);
    // uint kernelVirtualBlock = ALIGN_BLOCK((uint64)&__KERNEL_VIRT_SIZE) / 0x1000;
    // kprint("kernel virt block = %d for size %d\n", kernelVirtualBlock , (uint64)&__KERNEL_VIRT_SIZE);
    // kprint("Starting at address %x and end at address %x\n", (uint64)&__KERNEL_VIRT_LINK, (uint64)&__KERNEL_VIRT_END);
    // kprint("P4 %d  P3 %d  P2 %d  P1 %d\n", PML4_INDEX((uint64)&__KERNEL_VIRT_LINK), PDPT_INDEX((uint64)&__KERNEL_VIRT_LINK), PD_INDEX((uint64)&__KERNEL_VIRT_LINK), PT_INDEX((uint64)&__KERNEL_VIRT_LINK));
    // kprint("P4 %d  P3 %d  P2 %d  P1 %d\n", PML4_INDEX((uint64)&__KERNEL_VIRT_END), PDPT_INDEX((uint64)&__KERNEL_VIRT_END), PD_INDEX((uint64)&__KERNEL_VIRT_END), PT_INDEX((uint64)&__KERNEL_VIRT_END));
    // kprint("Low memory Index\n");
    // kprint("P4 %d  P3 %d  P2 %d  P1 %d\n", PML4_INDEX((uint64)0xb8000), PDPT_INDEX((uint64)0xb8000), PD_INDEX((uint64)0xb8000), PT_INDEX((uint64)0xb8000));
    kernelMapping();
    write_cr3((uint64)kernelPage->pml4);
}

/* same mapping as the first done at boot but with a static and dynamic kernel part */
void kernelMapping(void)
{
    kernelPage->pml4[PAGE_ENTRY_NBR - 0x1] = (uint64)(kernelPage->pdpt) | PRESENT | WRITABLE;
    kernelPage->pml4[0x0]                  = (uint64)(kernelPage->pdpt) | PRESENT | WRITABLE; // low pmm access

    kernelPage->pdpt[PAGE_ENTRY_NBR - 0x2] = (uint64)(kernelPage->pdt) | PRESENT | WRITABLE;
    kernelPage->pdpt[0x0]                  = (uint64)(kernelPage->pdt) | PRESENT | WRITABLE;

    kernelPage->pdt[0x0] = (uint64)(kernelPage->pt_kernel_static)  | PRESENT | WRITABLE;
    kernelPage->pdt[0x1] = (uint64)(kernelPage->pt_kernel_dynamic) | PRESENT | WRITABLE; // use for KHEAP

    for (uint16 i = 0; i < PAGE_ENTRY_NBR; i++)
        kernelPage->pt_kernel_static[i] = (FOURKIB_PAGESIZE * i) | PRESENT | WRITABLE; // | HUGE_PAGE | GLOBAL_PAGE;
}

void userSpaceAccess_RemapVMM(void)
{
    /* add a pdpt at pml4[1] for user access */
}
