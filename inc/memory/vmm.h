#ifndef _VMM_H_
#define _VMM_H_

#include "memory.h"
#include "eternity.h"
#include "sysdef.h"

struct vmmblock *vmmblock;

virtaddr_t allocate_page(uint size);
void free_page(virtaddr_t rect);
virtaddr_t kmem_request(uint size);
void mmap(virtaddr_t virt, physaddr_t phys, uint off);
void init_vmm(void);

#endif
