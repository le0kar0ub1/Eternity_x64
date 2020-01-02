#include "tss.h"
#include "descriptors.h"
#include "gdt.h"

struct tss_entry kernel_tss;

static uint8 kstack[0x1000];
static uint8 iststack[0x1000];

/* kernel/user space memory space switching */
void init_tss(void)
{
    uint8 gdtIdx = GDT_TSS_ENTRY;
    uint64 base = (uint64)&kernel_tss;
    set_gdt_entry(gdtIdx, base, base + sizeof(struct tss_entry), 0xE9, 0);
    // gdt_set_entry_byBit(gdtIdx, base, sizeof(struct tss_entry) - 0x1, 0x0, 0x9, 0x3);

    memset(&kernel_tss, 0, sizeof(struct tss_entry));

    uint64 stack = (uint64)kstack + 0x1000;
    kernel_tss.rsp0l = (uint32)stack;
    kernel_tss.rsp0h = (uint32)(stack >> 0x20);

    stack = (uint64)iststack + 0x1000;
    kernel_tss.ist1l = (uint32)stack;
    kernel_tss.ist1h = (uint32)(stack >> 0x20);
    flush_tss();
}

/* tss stack (wich stack pointer CPU must using)*/
void set_tss_stack(uint64 kss, uint64 krsp)
{
    kernel_tss.rsp0l = krsp;
    kernel_tss.rsp0h = krsp >> 0x20;
    flush_tss();
}