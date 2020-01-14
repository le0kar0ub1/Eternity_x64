#include "eternity.h"
#include "paging.h"
#include "pmm.h"
#include "memory.h"

extern uint64 __KERNEL_VIRT_SIZE;

void *fromIndexToAdrr(uint64 pml4, uint64 pdpt, uint64 pdt, uint64 pt)
{
    uint64 addr;

    addr = (((0x1 << 0x9) - (0x1 << 0x8)) & pml4) > 0x0 ? 0xffff000000000000 : 0x0;
    addr += pml4 << 0x27;
    addr += pdpt << 0x1E;
    addr += pdt  << 0x15;
    addr += pt   << 0x0C;
    return ((void *)addr);
}

void pageFault_handler(struct frame *frame)
{
    /* Page faults in kernel space leads to death */
     uint64 fault_addr = read_cr2(); /* read cr2 to get faulting address */

     vga_set_attrib(VGA_RED, VGA_BLACK);
     kprint("Page Fault at address : %x\n", fault_addr);
     /* error num pushed by CPU give info on page fault */
     if (!(frame->error & ERR_PF_PRES))
         kprint("No present in memory\n");
     if ((frame->error & ERR_PF_RW))
         kprint("Page is read only\n");
     if ((frame->error & ERR_PF_USER))
         kprint("Kernel page access\n");
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
