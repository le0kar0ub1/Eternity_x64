#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

#define PAGE_SIZE  0x1000

#define ALIGN_PAGE(x) (((x) & (MAX_ADDR_64B_SYS - (PAGE_SIZE - 0x1))) + 0x1000)

struct vmmblock {
    struct vmmblock *next;
    void *page;
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
