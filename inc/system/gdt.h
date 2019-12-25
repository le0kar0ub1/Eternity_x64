#ifndef _GDT_H_
#define _GDT_H_

#define NUM_GDT_DESCRIPTORS 0x6

#define GDT_ENTRY_SIZE 0x8

#define GDT_NULL_ENTRY        0x0
#define GDT_KERNEL_CODE_ENTRY 0x1
#define GDT_KERNEL_DATA_ENTRY 0x2
#define GDT_USER_CODE_ENTRY   0x3
#define GDT_USER_DATA_ENTRY   0x4
#define GDT_TSS_ENTRY         0x5

struct gdt_entry
{
    uint16 limit_low;
    uint16 base_low;
    uint8  base_middle;
    uint8  access;
    uint8  granularity;
    uint8  base_high;
} __attribute__((packed));

struct gdt_entry_bits {
    uint limit_low: 16;
    uint base_low : 24;
     // attribute byte split into bitfields
    uint accessed : 1;
    uint read_write : 1; // readable for code, writable for data
    uint conforming_expand_down : 1; // conforming for code, expand down for data
    uint code : 1; // 1 for code, 0 for data
    uint always_1 : 1; // should be 1 for everything but TSS and LDT
    uint DPL : 2; // priviledge level
    uint present : 1;
     // and now into granularity
    uint limit_high : 4;
    uint available : 1;
    uint null : 1; // should always be 0
    uint big  : 1; // 32bit opcodes for code, uint32_t stack for data
    uint gran : 1; // 1 to use 4k page addressing, 0 for byte addressing
    uint base_high :  8;
} __attribute__((packed));

void set_gdt_entry(uint index, uint32 base, uint32 limit, uint8 access, uint8 granularity);

#endif
