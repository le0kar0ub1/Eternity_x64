#ifndef _MSR_H_
#define _MSR_H_

#include "eternity.h"

/* syscall / sysret INTEL Init  */
#define MSR_IA32_SYSENTER_CS   0x174
#define MSR_IA32_SYSENTER_RSP  0x175
#define MSR_IA32_SYSENTER_RIP  0x176

#define MSR_IA32_BASE  0xC0000001
#define MSR_IA32_EFER  0xC0000080
#define MSR_IA32_STAR  0xC0000081
#define MSR_IA32_LSTAR 0xC0000082
#define MSR_IA32_MASK  0xC0000084

static inline uint64 rdmsr(uint64 msr)
{
    uint32 low, high;
    asm volatile ("rdmsr": "=a"(low), "=d"(high): "c"(msr));
    return (((uint64)high << 32) | low);
}

static inline void wrmsr(uint64 msr, uint64 value)
{
    uint32 low = value & 0xFFFFFFFF;
    uint32 high = value >> 32;
    asm volatile ("wrmsr":: "c"(msr), "a"(low), "d"(high));
}

/* define for msr ==  0xC0000080 */
#define MSR_SCE 0x0  // System Call Extensions
// 1-7 Reserved
#define MSR_LME   8  // Long Mode Enable
#define MSR_LMA   10 // Long Mode Active
#define MSR_NXE   11 // No-Execute Enable
#define MSR_SVME  12 // Secure Virtual Machine Enable
#define MSR_LMSLE 13 // Long Mode Segment Limit Enable
#define MSR_FFXSR 14 // Fast FXSAVE/FXRSTOR
#define MSR_TCE   15 // Translation Cache Extension
// 16-63 Reserved

#endif
