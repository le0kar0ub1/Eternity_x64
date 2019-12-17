#include "eternity.h"
#include "vmm.h"
#include "pmm.h"
#include "memory.h"

extern uint64 PML4;
extern uint64 PDPT;
extern uint64 PDT;

struct pageTable *kernelPageTable;

void init_vmm(void)
{
    kernelPageTable = (struct pageTable *)ALIGN_BLOCK((uint64)kernelPageTable);
    HVMmapping();
    uint64 virtAddr = ((uint64)kernelPageTable->pml4);
    write_cr3(virtAddr);
    hlt();
}

/* same mapping as the first done at boot but with a static and dynamic kernel part */
void HVMmapping(void)
{
    write_cr4(read_cr4() | HUGE_PAGE);

    kernelPageTable->pml4[PAGE_ENTRY_NBR - 0x1] = (uint64)(kernelPageTable->pdpt)               | PRESENT | WRITABLE;
    kernelPageTable->pdpt[PAGE_ENTRY_NBR - 0x2] = (uint64)(kernelPageTable->pdt_kernel_static)  | PRESENT | WRITABLE;
    kernelPageTable->pdpt[PAGE_ENTRY_NBR - 0x1] = (uint64)(kernelPageTable->pdt_kernel_dynamic) | PRESENT | WRITABLE;
    for (uint16 i = 0; i < PAGE_ENTRY_NBR; i++)
        kernelPageTable->pdt_kernel_static[i] = (0x200000 * i) | PRESENT | WRITABLE | HUGE_PAGE | GLOBAL_PAGE;
}

void userSpaceAccess_RemapVMM(void)
{

}
