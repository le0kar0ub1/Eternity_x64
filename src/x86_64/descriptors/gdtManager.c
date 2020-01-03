#include "eternity.h"
#include "gdt.h"
#include "descriptors.h"

extern uint *gdt;

void set_gdt_entry(uint index, uint32 base, uint32 limit, uint8 access, uint8 granularity)
{
    struct gdt_entry *entry = (struct gdt_entry *)((uint64)gdt + (index * GDT_ENTRY_SIZE));
    entry->base_low = base & 0xFFFF;
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;

    entry->limit_low = limit & 0xFFFF;
    entry->granularity = (limit >> 16) & 0x0F;

    entry->granularity |= granularity & 0xF0;
    entry->access = access;
}

void gdt_set_entry_byBit(uint index, uint32 base, uint32 limit, uint8 descType, uint8 type, uint8 dpl)
{
    struct gdt_entry_bits *entry = (struct gdt_entry_bits *)((uint64)gdt + (index * GDT_ENTRY_SIZE));
    memset(entry, 0x0, sizeof(struct gdt_entry_bits));

    entry->lowLimit = limit;
    entry->baseLow = base & 0xFFFF;
    entry->baseHigh = (base >> 16) & 0xFF;
    entry->type = type;
    entry->descType = descType;
    entry->dpl = dpl;
    entry->present = 0x1;
    entry->segLimit = 0x0;
    entry->available = 0x0;
    entry->longMode = 0x0;
    entry->db = 0x0;
    entry->granularity = 0x1;
    entry->baseHigh = (base >> 24) & 0xFF;
}