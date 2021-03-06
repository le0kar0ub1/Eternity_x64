#ifndef _IDT_H_
#define _IDT_H_

#define IDT_ENTRY_SIZE  0x10
#define IDT_ENTRY_NBR   0x100

struct idt_entry {
    uint16 offset_1; // offset bits 0..15
    uint16 selector; // a code segment selector in GDT or LDT
    uint8  ist;      // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8  type_attr;// type and attributes
    uint16 offset_2; // offset bits 16..31
    uint32 offset_3; // offset bits 32..63
    uint32 zero;     // reserved
} __packed;

#define IDR_PRESENT (1 << 0x7)

#define IDT_DPL0    ((1 << 0x5) * 0)
#define IDT_DPL1    ((1 << 0x5) * 1)
#define IDT_DPL2    ((1 << 0x5) * 2)
#define IDT_DPL3    ((1 << 0x5) * 3)

#define IDR_TASK_GATE  0x5
#define IDT_INT_GATE   0xE
#define IDT_TRAP_GATE  0xF

struct idt_ptr {
    uint16 limit;
    uint64 base;
} __packed;

void set_idt_entry(uint index, uint32 base, uint32 limit, uint8 access, uint8 granularity);
void idt_set_entry_byBit(uint index, uint32 base, uint32 limit, uint8 descType, uint8 type, uint8 dpl);


#endif