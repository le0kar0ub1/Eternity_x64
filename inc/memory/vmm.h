#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

#define MMU_PAGE_UNMAP 0x0

struct vmmblock {
    struct vmmblock *next;
    virtaddr_t page;
    uint  involved;
    uint8 used;
};

#define SIZEOF_VMMBLOCK sizeof(struct vmmblock)

struct vmmblock *vmmblock;

virtaddr_t allocate_page(uint size);
void free_page(virtaddr_t rect);
virtaddr_t kmem_request(uint size);
void mmap(virtaddr_t virt, physaddr_t phys, uint off);
void init_vmm(void);

#endif
