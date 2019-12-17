#include "eternity.h"
#include "vmm.h"
#include "memory.h"

extern uint64 PML4;
extern uint64 PDPT;
extern uint64 PDT;

struct pageTable kernelPageTable;

void init_vmm(void)
{
    HVMmapping(&kernelPageTable);
    kprint("%x   %x\n", kernelPageTable.pml4, V2P(kernelPageTable.pml4));
    write_cr3((uintptrs)V2P(kernelPageTable.pml4));
}

/* same mapping as the first done at boot but with a static and dynamic kernel part */
void HVMmapping(struct pageTable *pt)
{
    write_cr4(read_cr4() | HUGE_PAGE);

    pt->pml4[PAGE_ENTRY_NBR - 0x1] = V2P(pt->pdpt)               | PRESENT | WRITABLE;
    pt->pdpt[PAGE_ENTRY_NBR - 0x2] = V2P(pt->pdt_kernel_static)  | PRESENT | WRITABLE;
    pt->pdpt[PAGE_ENTRY_NBR - 0xA] = V2P(pt->pdt_kernel_dynamic) | PRESENT | WRITABLE;
    for (uint16 i = 0; i < PAGE_ENTRY_NBR; i++)
        pt->pdt_kernel_static[i] = (0x200000 * i) | PRESENT | WRITABLE | HUGE_PAGE | GLOBAL_PAGE;
}

void userSpaceAccess_RemapVMM(void)
{

}
