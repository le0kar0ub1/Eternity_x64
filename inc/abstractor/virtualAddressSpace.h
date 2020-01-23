#ifndef _VIRTUAL_ADDRESS_SPACE_H_
#define _VIRTUAL_ADDRESS_SPACE_H_

#include "typedef.h"
#include "virtualSegment.h"

struct vaspace {
    virtaddr_t virtRoot;
    physaddr_t physRoot;
    struct vseg *vseg;
    uint64       flag;
} __packed;

struct vaspace *vaspace_init(virtaddr_t virtRoot, physaddr_t physRoot, struct vseg *seg, uint64 flag);
void vaspace_free(void);

/* compile time implementaiton (this will be get from current thread) */
static inline struct vaspace *vaspace_current(void)
{
    return (NULL);
}

#endif