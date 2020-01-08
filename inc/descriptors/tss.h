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
} __packed;

/* the gdt tss entry is 128B long */
struct gdt_tss_entry {
    uint64 lowlimit  : 16; // segment extent (lsb)

    uint64 lowbase   : 24; // segment base address (lsb)

    uint64 type      : 5;  // segment type
    uint64 dpl       : 2;  // segment descriptor priority level
    uint64 pres      : 1;  // segment descriptor present

    uint64 highlimit : 4;  // segment extent (msb)
    uint64 xx1       : 3;  // avl, long and def32 (not used)
    uint64 gran      : 1;  // limit granularity (byte/page)

    uint64 highbase  : 40; // segment base address (msb)

    uint64 xx2       : 8;  // reserved
    uint64 zero      : 5;  // must be zero
    uint64 xx3       : 19; // reserved
} __packed;

#endif