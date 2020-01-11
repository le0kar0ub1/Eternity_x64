#ifndef _CPU_STATE_H
#define _CPU_STATE_H

#include "eternity.h"

struct cpuContext *getCpuContext(void);

/* STRUCT REPRESENTING A CPU STATE (CONTEXT) */
struct cpuContext {
    uint64 gs;      // 0x0
    uint64 fs;      // 0x8
    uint64 es;      // 0x10
    uint64 ds;      // 0x18

    uint64 r15;     // 0x20
    uint64 r14;     // 0x28
    uint64 r13;     // 0x30
    uint64 r12;     // 0x38
    uint64 r11;     // 0x40
    uint64 r10;     // 0x48
    uint64 r9;      // 0x50
    uint64 r8;      // 0x58

    uint64 rax;     // 0x60
    uint64 rcx;     // 0x68
    uint64 rdx;     // 0x70
    uint64 rbx;     // 0x78
    uint64 rsi;     // 0x80
    uint64 rdi;     // 0x88

    uint64 rbp;     // 0x90

    uint64 UNUSED1; // 0x98
    uint64 UNUSED2; // 0xA0

    uint64 rip;     // 0xA8
    uint64 cs;      // 0xB0
    uint64 rflags;  // 0xB8
    uint64 rsp;     // 0xC0
    uint64 ss;      // 0xC8

    /* UNREACHABLE FOR THE MOMENT */
    uint64 cr3;     // 0xD8

    // xmm0..xmm15, 128 bit registers
    // uint64 xmm[32]; // 0xE0
} __packed;

 #endif