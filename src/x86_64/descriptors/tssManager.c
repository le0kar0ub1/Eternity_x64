#include "tss.h"
#include "descriptors.h"
#include "gdt.h"

extern struct tss_entry tss;

extern uint64 tss_size;

extern uint64 gdt_start;
extern uint64 gdt_size;

void set_tss_entry(void)
{
    struct gdt_tss_entry *ptr = (struct gdt_tss_entry *)((uint64)&gdt_start + TSS_SELECTOR);

    ptr->lowlimit = (uint64)&tss_size;
    ptr->lowbase = ((uint64)&tss);
    ptr->type = 0x9;
    ptr->dpl = 0x0;
    ptr->pres = 0x1;
    ptr->highlimit = 0x0;
    ptr->gran = 0x1;
    ptr->highbase = ((uint64)&tss) >> 0x18;
}

/* kernel/user space memory space switching */
void init_tss(void)
{
    set_tss_entry();
    flush_gdt((uint64)&gdt_start, (uint64)&gdt_size);
    flush_tss(TSS_SELECTOR); // | 0x3 for dpl3
}

/* tss stack (wich stack pointer CPU must using)*/
void set_tss_stack(uint64 ist, uint8 istnbr, uint64 krsp, uint8 rspnbr)
{
    uint64 *shiftRsp = &(tss.rsp0);
    uint64 *shiftIst = &(tss.ist1);
    if (krsp && rspnbr < 0x3) {
        shiftRsp += (rspnbr * 0x8);
        *shiftRsp = krsp;
    }
    if (ist && istnbr < 0x8) {
        shiftIst += (istnbr * 0x8);
        *shiftIst = krsp;
    }
    flush_tss(TSS_SELECTOR);
}