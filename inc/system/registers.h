#include "eternity.h"

#ifndef _REGISTERS_H_
#define _REGISTERS_H_

struct regs {
    uint64 flags;
    uint64 rdi;
    uint64 rsi;
    uint64 rbx;
    uint64 rdx;
    uint64 rcx;
    uint64 rax;

    uint64 ds;
    uint64 es;
    uint64 ss;
    uint64 fs;
    uint64 gs;
    uint64 cs;

    uint64 rsp;
    uint64 rbp;
    uint64 rip;
};

void print_registers(struct regs);
void dump_registers(void);

#endif
