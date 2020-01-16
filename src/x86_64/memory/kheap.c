#include "eternity.h"
#include "kheap.h"

virtaddr_t kheap_start;
struct kheap *kheap;
struct kheap *kheap_curblock;
virtaddr_t kheap_end;

void dump_kheap(void)
{
    for (struct kheap *root = kheap; root; root = root->next)
        kprint("BLOCK at %x sizeof %x\n", (uint64)root + SIZEOF_KHEAPBLOCK, root->size);
    kprint("\n");
}

extern virtaddr_t boostrap;
void init_kalloc(void)
{
    /* panic if segment intersect */
    assert_gt((uint64)boostrap, KHEAP_BASE_START);
    kheap_start = (virtaddr_t)KHEAP_BASE_START;
    kheap = (virtaddr_t)KHEAP_BASE_START;
    kheap_end = (virtaddr_t)KHEAP_BASE_END;
    /* init a block to get a fast mallo */
    kheap->next = NULL;
    kheap->size = 0x10;
    kheap->used = false;
    kheap_curblock = kheap;
}

virtaddr_t kheap_get_free(uint size, struct kheap *kheap)
{
    while (kheap) {
        if (kheap->size <= size && !kheap->used) {
            kheap->used = true;
            return ((virtaddr_t)kheap + SIZEOF_KHEAPBLOCK);
        }
        kheap = kheap->next;
    }
    return (NULL);
}

virtaddr_t kheap_new_block(uint size)
{
    kheap_curblock->next = (struct kheap *)((uint64)kheap_curblock + kheap_curblock->size + SIZEOF_KHEAPBLOCK);
    kheap_curblock = kheap_curblock->next;
    kheap_curblock->size = size;
    kheap_curblock->used = true;
    kheap_curblock->next = NULL;
    return ((virtaddr_t)kheap_curblock + SIZEOF_KHEAPBLOCK);
}

virtaddr_t kalloc(uint size)
{
    virtaddr_t allocated = NULL;
    kheap = (struct kheap *)kheap_start;

    allocated = kheap_get_free(size, kheap);   
    if (allocated)
        return (allocated);
    else
        allocated = kheap_new_block(size);
    if (!allocated)
        PANIC("Kernel is running out of kheap\n");
    return (allocated);
}

void kfree(virtaddr_t ptr)
{
    kheap = (struct kheap *)kheap_start;
    while (kheap) {
        if ((virtaddr_t)((uint64)kheap + SIZEOF_KHEAPBLOCK) == ptr)
            goto tryMerge;
        kheap = kheap->next;
    }
    PANIC("Invalid pointer in free\n");
tryMerge:
    if (kheap->next && kheap->next->used == false) {
        kheap->size += kheap->next->size;
        kheap->next = kheap->next->next;
    }
    kheap->used = false;
}