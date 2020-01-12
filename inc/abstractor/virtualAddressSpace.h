#ifndef _VIRTUAL_ADDRESS_SPACE_H_
#define _VIRTUAL_ADDRESS_SPACE_H_

#include "typedef.h"
#include "virtualSegment.h"

struct vaspace {
    struct vseg *vseg;
    uint64       flag;
}

#endif