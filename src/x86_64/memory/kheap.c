#include "eternity.h"
#include "kheap.h"

struct kheap *kheap;
uint64 kheapPageCycle;
uint64 pageAllocated;

void dump_kheap(void)
{
    for (struct kheap *root = kheap; root; root = root->next)
        kprint("BLOCK at %x sizeof %x used %d\n", (uint64)root + SIZEOF_KHEAPBLOCK, root->size, root->used);
    kprint("\n");
}

virtaddr_t find_free_block(struct kheap **root, uint size)
{
    for (; (*root)->next; (*root) = (*root)->next) {
        if ((*root)->size <= size && !(*root)->used) {
            (*root)->used = true;
            return ((virtaddr_t)(*root) + SIZEOF_KHEAPBLOCK);
        }
    }
    return ((virtaddr_t)-1);
}

virtaddr_t kalloc(uint size)
{
    if (!size)
        return (NULL);
    struct kheap *root = kheap;
    virtaddr_t new; // if all mem consumed;
    if ((new = find_free_block(&root, size)) != (virtaddr_t)-1)
        return (new);
    if (kheapPageCycle + size + SIZEOF_KHEAPBLOCK > PAGE_SIZE * pageAllocated) {
        new = kmem_request(size + SIZEOF_KHEAPBLOCK);
        root->next = (virtaddr_t)(new);
        kheapPageCycle = 0x0;
        pageAllocated = ALIGN_FRAME(size + SIZEOF_KHEAPBLOCK) / PAGE_SIZE;
    } else
        root->next = (virtaddr_t)root + root->size + SIZEOF_KHEAPBLOCK;
    root = root->next;
    root->next = NULL;
    root->size = size;
    root->used = true;
    kheapPageCycle += size + SIZEOF_KHEAPBLOCK;
    return ((virtaddr_t)((uint64)root + SIZEOF_KHEAPBLOCK));
}

void init_kalloc(void)
{
    virtaddr_t begin = kmem_request(PAGE_SIZE);
    kheap = (struct kheap *)begin;
    kheap->next = NULL;
    kheap->size = 0x10;
    kheap->used = false;
    kheapPageCycle = kheap->size + SIZEOF_KHEAPBLOCK;
    pageAllocated = 0x1;
}

/* for the moment just let the segment & set size to 0 == free */
void kfree(virtaddr_t ptr)
{
    struct kheap *root = kheap;

    for (; root; root = root->next) {
        if ((virtaddr_t)root + SIZEOF_KHEAPBLOCK == ptr) {
            root->used = false;
            return;
        }
    }
    PANIC("Invalid pointer in free request: %x\n", ptr);
}
