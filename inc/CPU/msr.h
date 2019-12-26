#ifndef _MSR_H_
#define _MSR_H_

#include "eternity.h"

enum msr_id {MSR_APIC_BASE = 0x1B};

static inline uint64 read_msr(enum msr_id msr)
{
    uint32 low;
    uint32 high;

    asm volatile("rdmsr" : "=a"(low), "=d"(high) : "c"((uint32)msr));
    return (((uint64)high << 32u) | (uint64)low);
}

static inline void write_msr(enum msr_id msr, uint64 val)
{
    uint32 low;
    uint32 high;

    low = (uint32)val;
    high = (uint32)(val >> 32u);
    asm volatile("wrmsr" : : "a"(low), "d"(high), "c"((uint32)msr));
}

#endif
