#ifndef _TSS_H
#define _TSS_H

#include "eternity.h"

/* IST is Interrupt Stack Table (used to mapp system call) */
struct tss_entry {
    uint32 reserved0;
    uint64 rsp0;
    uint64 rsp1;
    uint64 rsp2;
    uint64 reserved1;
    uint64 ist1;
    uint64 ist2;
    uint64 ist3;
    uint64 ist4;
    uint64 ist5;
    uint64 ist6;
    uint64 ist7;
    uint64 reserved2;
    uint16 reserved3;
    uint16 ioMapBaseAddr;
};

#endif