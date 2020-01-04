#ifndef _CPU_STATE_H
#define _CPU_STATE_H

#include "eternity.h"

/* STRUCT REPRESENTING A CPU STATE (CONTEXT) */
struct cpuState {
    uint64 rax;
    uint64 rbx;
    uint64 rcx;
    uint64 rdx;
    uint64 rsi;
    uint64 rdi;
    uint64 rsp;

    uint64 r8;
    uint64 r9;
    uint64 r10;
    uint64 r11;
    uint64 r12;
    uint64 r13;
    uint64 r14;
    uint64 r15;

    uint64 cs; // code segment
    uint64 ss; // data segment

    uint64 ds;
    uint64 gs;
    uint64 fs;
    uint64 es;

    uint64 rip;
    uint64 rflags;
    uint64 rbp;

    uint64 cr3;

    uint64 xmm[32]; // xmm0..xmm15, 128 bit registers
} __packed;

 #endif