#ifndef _PROCESSUS_H_
#define _PROCESSUS_H_

#include "eternity.h"
#include "scheluder.h"

#define SCHED_TOLERANCE 5

enum threadState {
    THREAD_RUNNING          = 0,
    THREAD_INTERRUPTIBLE    = 1,
    THREAD_UNINTERRUPTIBLE  = 2,
    THREAD_ZOMBIE           = 4,
    THREAD_STOPPED          = 8,
    THREAD_SWAPPING         = 16,
    THREAD_EXCLUSIVE        = 32,
    THREAD_CREATED          = 64,
    THREAD_LOADING          = 128
};

typedef uint64 pid_t;

struct context {
    uint64 eflags;
    uint64 r15;
    uint64 r14;
    uint64 r13;
    uint64 r12;
    uint64 r11;
    uint64 r10;
    uint64 r9;
    uint64 r8;
    uint64 rbp;
    uint64 rax;
    uint64 rdi;
    uint64 rsi;
    uint64 rdx;
    uint64 rcx;
    uint64 rbx;
    uint64 rsp;
    uint32 ds;
    uint32 gs;
    uint32 fs;
    uint32 es;
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
    pid_t pid;
    void *stack;
    uint32 state;
    uint32 lifeCycle;
    // void *page_dir;
};

void init_process(void);
pid_t new_pid(void);

#endif