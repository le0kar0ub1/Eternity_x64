#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

struct vmmblock {
    struct vmmblock *next;
    virtaddr page;
    uint  involved;
    uint8 used;
};

#define SIZEOF_VMMBLOCK sizeof(struct vmmblock)

struct vmmblock *vmmblock;

virtaddr allocate_page(uint size);
void free_page(virtaddr rect);
virtaddr kmem_request(uint size);
void mmap(virtaddr virt, physaddr phys, uint off);
void init_vmm(void);

#endif
