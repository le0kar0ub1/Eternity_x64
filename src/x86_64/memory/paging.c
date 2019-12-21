#include "eternity.h"
#include "paging.h"
#include "pmm.h"
#include "memory.h"

extern uint64 PML4;
extern uint64 PDPT;
extern uint64 PDT;

extern uint64 __KERNEL_VIRT_SIZE;

struct pageTable *kpage;

void *fromIndexToAdrr(uint64 pml4, uint64 pdpt, uint64 pdt, uint64 pt)
{
    uint64 addr;

    addr = (((0x1 << 0x9) - (0x1 << 0x8)) & pml4) > 0 ? 0xffff000000000000 : 0;
    addr += pml4 << 0x27;
    addr += pdpt << 0x1E;
    addr += pdt  << 0x15;
    addr += pt   << 0x0C;
    return ((void *)addr);
}

void init_kpaging(void)
{
    kpage = (struct pageTable *)ALIGN_BLOCK((uint64)kpage);
    // uint kernelVirtualBlock = ALIGN_BLOCK((uint64)&__KERNEL_VIRT_SIZE) / 0x1000;
    // kprint("kernel virt block = %d for size %d\n", kernelVirtualBlock , (uint64)&__KERNEL_VIRT_SIZE);
    // kprint("Starting at address %x and end at address %x\n", (uint64)&__KERNEL_VIRT_LINK, (uint64)&__KERNEL_VIRT_END);
    // kprint("P4 %d  P3 %d  P2 %d  P1 %d\n", PML4_INDEX((uint64)&__KERNEL_VIRT_END), PDPT_INDEX((uint64)&__KERNEL_VIRT_END), PD_INDEX((uint64)&__KERNEL_VIRT_END), PT_INDEX((uint64)&__KERNEL_VIRT_END));
    // kprint("Low memory Index\n");
    // kprint("P4 %d  P3 %d  P2 %d  P1 %d\n", PML4_INDEX((uint64)0xb8000), PDPT_INDEX((uint64)0xb8000), PD_INDEX((uint64)0xb8000), PT_INDEX((uint64)0xb8000));
    kernelMapping();
    write_cr3((uint64)kpage->pml4);
}

/* same mapping as the first done at boot but with a static and dynamic kernel part */
void kernelMapping(void)
{
    kpage->pml4[KERNEL_PML4_ENTRY] = (uint64)(kpage->pdpt) | PRESENT | WRITABLE;
    kpage->pml4[0x0]               = (uint64)(kpage->pdpt) | PRESENT | WRITABLE; // low pmm access

    kpage->pdpt[KERNEL_PDPT_ENTRY] = (uint64)(kpage->pdt) | PRESENT | WRITABLE;
    kpage->pdpt[0x0]               = (uint64)(kpage->pdt) | PRESENT | WRITABLE;

    kpage->pdt[KERNEL_STATIC_PDT_ENTRY]    = (uint64)(kpage->pt_kernel_static) | PRESENT | WRITABLE;
    for (uint16 i = KERNEL_STATIC_PDT_ENTRY + 0x1; i < PAGE_ENTRY_NBR; i++)
        kpage->pdt[i] = (uint64)(kpage->pt_kernel_dynamic[i - 0x1]) | PRESENT | WRITABLE;

    for (uint16 i = 0; i < PAGE_ENTRY_NBR; i++)
        kpage->pt_kernel_static[i] = (FOURKIB_PAGESIZE * i) | PRESENT | WRITABLE; // | GLOBAL_PAGE;
}

void userSpaceAccess_RemapVMM(void)
{
    /* add a pdpt at pml4[1] for user access */
}

void pageFault_handler(struct frame *frame)
{
    /* Page faults in kernel space leads to death */
     uint64 fault_addr = read_cr2(); /* read cr2 to get faulting address */

     vga_set_attrib(VGA_RED, VGA_BLACK);
     kprint("Page Fault at address : %x\n", fault_addr);
     /* error num pushed by CPU give info on page fault */
     if (!(frame->error & ERR_PF_PRES))
         kprint("NO present in memory\n");
     if (frame->error & ERR_PF_RW)
         kprint("RDONLY\n");
     if (frame->error & ERR_PF_USER)
         kprint("CPU user-mode\n");
     if (frame->error & ERR_PF_RES)
         kprint("Overwritten CPU-reserved bits of page entry\n");
     if (frame->error & ERR_PF_INST)
         kprint("Instruction fetch\n");
     hlt();
}

void init_pf_handler(void)
{
    register_int_handler(INT_PAGE_FAULT, pageFault_handler);
}
