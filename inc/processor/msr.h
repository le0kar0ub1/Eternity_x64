#ifndef _MSR_H_
#define _MSR_H_

#include "eternity.h"

/* syscall init useful values */
#define MSR_IA32_STAR   0xc0000081
#define MSR_IA32_LSTAR  0xc0000082
#define MSR_IA32_FMASK  0xc0000084

static inline uint64 rdmsr(uint32 id)
{
    uint64 value;
    asm volatile ("rdmsr": "=A" (value): "c" (id));
    return value;
}

static inline void wrmsr(uint32 id, uint64 value)
{
    asm volatile ("wrmsr":: "c" (id), "A" (value));
}

#endif
