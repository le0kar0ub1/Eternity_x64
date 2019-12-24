#include "eternity.h"
#include "gdt.h"

extern uint *gdt;

void set_gdt_entry(uint index, uint32 base, uint32 limit, uint8 access, uint8 granularity)
{
    struct gdt_entry *entry = (struct gdt_entry *)(gdt + (index * GDT_ENTRY_SIZE));
    entry->base_low = base & 0xFFFF;
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24 & 0xFF);

    entry->limit_low = limit & 0xFFFF;
    entry->granularity = (limit >> 16) & 0x0F;
    entry->access = access;
    entry->granularity = entry->granularity | (granularity & 0xF0);
}
