#include "eternity.h"
#include "vmm.h"
#include "pmm.h"
#include "memory.h"

extern uint64 PML4;
extern uint64 PDPT;
extern uint64 PDT;

struct pageTable *kernelPage;

void init_vmm(void)
{
    kernelPage = (struct pageTable *)ALIGN_BLOCK((uint64)kernelPage);
    HVMmapping();
    uint64 virtAddr = ((uint64)kernelPage->pml4);
    write_cr3(virtAddr);
    // hlt();
}

/* same mapping as the first done at boot but with a static and dynamic kernel part */
void HVMmapping(void)
{
    write_cr4(read_cr4() | HUGE_PAGE);

    kernelPage->pml4[PAGE_ENTRY_NBR - 0x1] = (uint64)(kernelPage->pdpt) | PRESENT | WRITABLE;
    kernelPage->pml4[0x0] =                  (uint64)(kernelPage->pdpt) | PRESENT | WRITABLE;

    kernelPage->pdpt[PAGE_ENTRY_NBR - 0x2] = (uint64)(kernelPage->pdt_kernel_static)  | PRESENT | WRITABLE;
    kernelPage->pdpt[PAGE_ENTRY_NBR - 0x1] = (uint64)(kernelPage->pdt_kernel_dynamic) | PRESENT | WRITABLE;
    kernelPage->pdpt[0x0]                  = (uint64)(kernelPage->pdt_kernel_static)  | PRESENT | WRITABLE;
    for (uint16 i = 0; i < PAGE_ENTRY_NBR; i++)
        kernelPage->pdt_kernel_static[i] = (0x200000 * i) | PRESENT | WRITABLE | HUGE_PAGE | GLOBAL_PAGE;
}

void userSpaceAccess_RemapVMM(void)
{
}
