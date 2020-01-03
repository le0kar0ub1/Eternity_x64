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
#define GDT_NULL_ENTRY2       0x6

struct gdt_entry {
    uint16 limit_low;
    uint16 base_low;
    uint8  base_middle;
    uint8  access;
    uint8  granularity;
    uint8  base_high;
} __packed;

struct gdt_entry_bits {
    uint16 lowLimit;
    uint16 baseLow;
    uint8  baseMid;
    uint8  type : 4;        // segment type
    uint8  descType : 1;    // 0 system, 1 code/data
    uint8  dpl : 2;
    uint8  present : 1;
    uint8  segLimit : 4;
    uint8  available : 1;
    uint8  longMode : 1;           // 64 bit segment
    uint8  db : 1;          // n.b. must be 0 in 64 bit
    uint8  granularity : 1; // 0: bytes, 1: 4KB
    uint8  baseHigh;
} __packed;

void set_gdt_entry(uint index, uint32 base, uint32 limit, uint8 access, uint8 granularity);
void gdt_set_entry_byBit(uint index, uint32 base, uint32 limit, uint8 descType, uint8 type, uint8 dpl);


#endif
