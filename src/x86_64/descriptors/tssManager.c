#include "tss.h"
#include "descriptors.h"
#include "gdt.h"

extern struct tss_entry tss;

extern uint64 tss_size;

extern uint64 gdt_start;
extern uint64 gdt_size;

void set_tss_entry(void)
{
    struct gdt_tss_entry *ptr = (struct gdt_tss_entry *)(&gdt_start + TSS_SELECTOR);
    // ptr[0x2] = tss_addr[0x0];
    // ptr[0x3] = tss_addr[0x1];
    // ptr[0x4] = tss_addr[0x2];
    // ptr[0x5] = 0x89; // Present | Executable | Accessed
    // ptr[0x7] = tss_addr[0x3];
    // ptr[0x8] = tss_addr[0x4];
    // ptr[0x9] = tss_addr[0x5];
    // ptr[0xA] = tss_addr[0x6];
    // ptr[0xB] = tss_addr[0x7];

    ptr->lowlimit = sizeof(struct gdt_tss_entry) - 0x1;
    ptr->lowbase = ((uint64)&tss);
    ptr->type = 0x9; // 386 TSS
    ptr->dpl = 0x0;
    ptr->pres = 0x1;
    ptr->highlimit = 0x0;
    ptr->gran = 0x0;
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