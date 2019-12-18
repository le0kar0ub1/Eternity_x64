#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"

struct vmmblock {
    struct vmmblock *next;
    // uint;
    uint8 used;
};

#endif
