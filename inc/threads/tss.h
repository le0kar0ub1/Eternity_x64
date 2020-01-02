#ifndef _TSS_H
#define _TSS_H

#include "eternity.h"

// struct tss_entry {
//     uint64 prevTss;
//     uint64 esp0;
//     uint64 ss0;
//     uint64 esp1;
//     uint64 ss1;
//     uint64 esp2;
//     uint64 ss2;
//     uint64 cr3;
//     uint64 rip;
//     uint64 eflags;
//     uint64 rax;
//     uint64 rcx;
//     uint64 rdx;
//     uint64 rbx;
//     uint64 rsp;
//     uint64 rbp;
//     uint64 rsi;
//     uint64 rdi;
//     uint64 es;
//     uint64 cs;
//     uint64 ss;
//     uint64 ds;
//     uint64 fs;
//     uint64 gs;
//     uint64 ldt;
//     uint16 trap;
//     uint16 iomap;
// };

struct tss_entry {
    uint32 reserved0;
    uint32 rsp0l;
    uint32 rsp0h;
    uint32 rsp1l;
    uint32 rsp1h;
    uint32 rsp2l;
    uint32 rsp2h;
    uint32 reserved1[2];
    uint32 ist1l;
    uint32 ist1h;
    uint32 ist2l;
    uint32 ist2h;
    uint32 ist3l;
    uint32 ist3h;
    uint32 ist4l;
    uint32 ist4h;
    uint32 ist5l;
    uint32 ist5h;
    uint32 ist6l;
    uint32 ist6h;
    uint32 ist7l;
    uint32 ist7h;
    uint32 reserved2[2];
    uint16 reserved3;
    uint16 ioMapBaseAddr;
};

#endif