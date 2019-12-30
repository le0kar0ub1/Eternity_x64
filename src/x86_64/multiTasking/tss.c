#include "tss.h"
#include "descriptors.h"

struct tss_entry kernel_tss;

/* kernel/user space memory space switching */
void init_tss(uint32 idx, uint64 kss, uint64 kstack_pointer)
{
    uint64 base = (uint64)&kernel_tss;
    set_gdt_entry(idx, base, base + sizeof(struct tss_entry), 0xE9, 0);
    /* Kernel tss, access(E9 = 1 11 0 1 0 0 1)
        1   present
        11  ring 3
        0   should always be 1, why 0? may be this value doesn't matter at all
        1   code?
        0   can not be executed by ring lower or equal to DPL,
        0   not readable
        1   access bit, always 0, cpu set this to 1 when accessing this sector(why 0 now?)
    */
    memset(&kernel_tss, 0, sizeof(struct tss_entry));
    kernel_tss.ss0 = kss;
    // Note that we usually set tss's esp to 0 when booting our os, however, we need to set it to the real esp when we've switched to usermode because
    // the CPU needs to know what esp to use when usermode app is calling a kernel function(aka system call), that's why we have a function below called tss_set_stack
    kernel_tss.esp0 = kstack_pointer;
    kernel_tss.cs = 0x0b;
    kernel_tss.ds = 0x13;
    kernel_tss.es = 0x13;
    kernel_tss.fs = 0x13;
    kernel_tss.gs = 0x13;
    kernel_tss.ss = 0x13;
    flush_tss();
}

/* tss stack (wich stack pointer CPU must using)*/
void set_tss_stack(uint64 kss, uint64 krsp)
{
    kernel_tss.ss0 = kss;
    kernel_tss.esp0 = krsp;
}