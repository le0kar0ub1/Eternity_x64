#ifndef _CPU_DESCRIPTOR_H_
#define _CPU_DESCRIPTOR_H_

#include "eternity.h"
#include "atomic.h"

typedef uint8 cpuid_t;

struct cpu {
    struct task *current_task;
    virtaddr_t safe_rsp; // syscall usage
    virtaddr_t tss;
    uint64_t preempt_count; // +1 when lock / -1 when unlock

    atomic32_t int_depth;
    bool reschedule;

    cpuid_t id;
    uint8 apic_id;
};

#endif
