#include "virtualAddressSpace.h"
#include "memory.h"

struct vaspace *vaspace_init(virtaddr_t virtRoot, physaddr_t physRoot, struct vseg *seg, uint64 flag)
{
    struct vaspace *space = kalloc(sizeof(struct vaspace));

    space->virtRoot = virtRoot;
    space->physRoot = physRoot;
    space->vseg     = seg;
    space->flag     = flag;
    return (space);
}

void vaspace_free(void)
{
    virtaddr_t root = get_current_pml4();
    struct vaspace *vaspace = vaspace_current();

    fatalAssert(vaspace);
    vseg_free(root, vaspace->vseg);
    kfree(vaspace);
}