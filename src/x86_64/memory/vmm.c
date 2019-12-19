#include "vmm.h"

/* start a the end of kernel phys */
uint64 vmmStart = (uint64)(&__KERNEL_VIRT_END);
uint64 vmmEnd = vmmStart + (MAX_ADDR_64B_SYS - vmmStart);

void init_vmm(void)
{
    vmmStart = ALIGN_BLOCK(vmmStart);
    vmmEnd   = ALIGN_BLOCK(vmmEnd) - PAGE_SIZE;
}

void mmap(void *frame, void *page)
{

}
