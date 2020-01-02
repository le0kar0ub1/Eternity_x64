#ifndef _DESCRIPTORS_H
#define _DESCRIPTORS_H

#include "typedef.h"

#define IDT_ENTRY_SIZE  0x10
#define IDT_ENTRY_NBR   0x100

#define GDT_ENTRY_SIZE 0x8
#define GDT_ENTRY_NBR  0x5

#define NULL_SELECTOR           0x00
#define KERNEL_CODE_SELECTOR    0x08
#define KERNEL_DATA_SELECTOR    0x10
#define USER_CODE_SELECTOR      0x18
#define USER_DATA_SELECTOR      0x20
#define TSS_SELECTOR            0x28

void flush_gdt(void);
void set_gdt_entry(uint index, uint32 base, uint32 limit, uint8 access, uint8 granularity);

void flush_idt(void);

void flush_tss(void);
void set_tss_stack(uint64 ist, uint8 istnbr, uint64 krsp, uint8 rspnbr);
void init_tss(void);

#endif