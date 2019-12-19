#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

#define PAGE_SIZE  0x1000

#define ALIGN_BLOCK(x) (((x) & (MAX_ADDR_64B_SYS - (PAGE_SIZE - 0x1))) + 0x1000)

struct vmmblock {
    struct vmmblock *next;
    // uint;
    uint8 used;
};

struct vmmblock *vmmblock;

#endif
