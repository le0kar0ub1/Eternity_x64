#ifndef _PROCESSUS_H_
#define _PROCESSUS_H_

#include "eternity.h"

#define SCHED_TOLERANCE 5

enum threadState {
    TASK_RUNNING          = 0,
    TASK_INTERRUPTIBLE    = 1,
    TASK_UNINTERRUPTIBLE  = 2,
    TASK_ZOMBIE           = 4,
    TASK_STOPPED          = 8,
    TASK_SWAPPING         = 16,
    TASK_EXCLUSIVE        = 32,
    TASK_CREATED          = 64,
    TASK_LOADING          = 128
};

typedef uint64 pid;

struct context {
    uint32 ds;
    uint32 gs;
    uint32 fs;
    uint32 es;
    uint64 r15;
    uint64 r14;
    uint64 r13;
    uint64 r12;
    uint64 r11;
    uint64 r10;
    uint64 r9;
    uint64 r8;
    uint64 rax;
    uint64 rcx;
    uint64 rdx;
    uint64 rbx;
    uint64 rsp;
    uint64 rbp;
    uint64 rsi;
    uint64 rdi;
    uint64 eflags;
    uint64 cr3;
    uint64 rip;
    unsigned long long xmm15;
    unsigned long long xmm14;
    unsigned long long xmm13;
    unsigned long long xmm12;
    unsigned long long xmm11;
    unsigned long long xmm10;
    unsigned long long  xmm9;
    unsigned long long  xmm8;
    unsigned long long  xmm7;
    unsigned long long  xmm6;
    unsigned long long  xmm5;
    unsigned long long  xmm4;
    unsigned long long  xmm3;
    unsigned long long  xmm2;
    unsigned long long  xmm1;
    unsigned long long  xmm0;
};

struct processDescriptor {
    char filename[0x100];
    struct context context;
    pid pid;
    virtaddr stack;
    uint32 state;
    uint32 lifeCycle;
    virtaddr *page_dir;
};

void init_process(void);
pid new_pid(void);

#endif