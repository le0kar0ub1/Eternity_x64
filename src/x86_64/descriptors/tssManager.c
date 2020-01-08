#include "tss.h"
#include "descriptors.h"
#include "gdt.h"

extern struct tss_entry tss;

extern uint64 tss_size;

extern uint64 gdt_start;
extern uint64 gdt_size;

void set_tss_entry(void)
{
    uint8 *ptr8 = (uint8 *)(&gdt_start + TSS_SELECTOR);
    uint8 tss_addr[0x8];
    memcpy(tss_addr, &tss, 0x8);
    ptr8[0x2] = tss_addr[0x0];
    ptr8[0x3] = tss_addr[0x1];
    ptr8[0x4] = tss_addr[0x2];
    ptr8[0x5] = 0x89; // Present | Executable | Accessed
    ptr8[0x7] = tss_addr[0x3];
    ptr8[0x8] = tss_addr[0x4];
    ptr8[0x9] = tss_addr[0x5];
    ptr8[0xA] = tss_addr[0x6];
    ptr8[0xB] = tss_addr[0x7];
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