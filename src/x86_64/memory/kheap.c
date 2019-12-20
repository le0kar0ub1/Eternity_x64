#include "eternity.h"
#include "kheap.h"

struct kheap *kheap;
uint64 kheapPageCycle;

virtaddr kheapManagerStart;

void dump_kheap(void)
{
    for (struct kheap *root = kheap; kheap; kheap = kheap->next)
        kprint("BLOCK at %x sizeof %x used %d\n", root + SIZEOF_KHEAPBLOCK, root->size, root->used);
}

virtaddr kalloc(uint size)
{
    if (!size)
        return (NULL);
    struct kheap *root = kheap;
    for (; root->next; root = root->next)
        if (root->size <= size && !root->used) {
            root->used = true;
            return ((virtaddr)root + SIZEOF_KHEAPBLOCK);
        }
    if (kheapPageCycle + size + SIZEOF_KHEAPBLOCK > PAGE_SIZE)
        PANIC("No VMM available\n");
    root->next = root + root->size + SIZEOF_KHEAPBLOCK;
    root = root->next;
    root->next = NULL;
    root->size = size;
    root->used = true;
    kheapPageCycle += root->size + SIZEOF_KHEAPBLOCK;
    return ((virtaddr)root + SIZEOF_KHEAPBLOCK);
}

void init_kalloc(void)
{
    kheapManagerStart = fromIndexToAdrr(KERNEL_PML4_ENTRY, KERNEL_PDPT_ENTRY, KERNEL_DYNAMIC_PDT_ENTRY, 0x0);
    kheap = (struct kheap *)kheapManagerStart;
    kheap->next = NULL;
    kheap->size = 0x10;
    kheap->used = false;
    kheapPageCycle = kheap->size + SIZEOF_KHEAPBLOCK;
}

/* for the moment just let the segment & set size to 0 == free */
void kfree(virtaddr ptr)
{
    struct kheap *root = kheap;

    for (; root; root = root->next) {
        if ((virtaddr)root + SIZEOF_KHEAPBLOCK == ptr) {
            root->used = false;
            return;
        }
    }
    PANIC("Invalid pointer in kfree\n");
}
