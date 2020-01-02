#ifndef _TSS_H
#define _TSS_H

#include "eternity.h"

/* IST is Interrupt Stack Table (used to mapp system call) */
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