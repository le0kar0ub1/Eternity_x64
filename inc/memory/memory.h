#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "eternity.h"
#include "sysdef.h"
#include "pagedef.h"

/* page define at boot are accessed with translation */
#define V2P(x) ((uint64)x - (uint64)(&__KERNEL_VIRT_BASE))
#define P2V(x) ((uint64)x + (uint64)(&__KERNEL_VIRT_BASE))

typedef uintptr physaddr_t;
typedef void    *virtaddr_t;

#define K 0x400
#define M (0x400 * K)
#define G (0x400 * M)

/* paging memory */
void identity_mapp(void);
void map_memory(ulong addr);
void *fromIndexToAdrr(uint64 pml4, uint64 pdpt, uint64 pdt, uint64 pt);
/* boostrap */
virtaddr_t boostrap_kalloc(uint64 size);
void boostrap_allocate_page(pml4_t *root, virtaddr_t virt, uint32 flag);

/* high level */
void kfree(void *ptr);
virtaddr_t kalloc(uint size);

/* toolchain  */
uintptr virtToPhys(pml4_t *root, virtaddr_t virt);
void switch_pml4(pml4_t *root, pml4_t *new);
void allocate_page(pml4_t *root, virtaddr_t virt, uint32 flag);
void free_page(pml4_t *root, virtaddr_t virt);
void mmap(pml4_t *root, virtaddr_t page, physaddr_t frame, int flags);
void allocate_segment(pml4_t *root, virtaddr_t start, virtaddr_t end, uint flag);
void mmap_segment(pml4_t *root, virtaddr_t start, virtaddr_t end, physaddr_t frame, uint flag);
void free_segment(pml4_t *root, virtaddr_t start, virtaddr_t end);
virtaddr_t physical_mmap(pml4_t *root, physaddr_t phys, uint size, int flag);
void mark_pmm_as_allocated(physaddr_t start, physaddr_t end);

/* invalid a page of TLB (TLB increase speed if addr was already accessed) */
static inline void invlpg(void *addr)
{
    asmv("invlpg (%0)" :: "r"(addr) : "memory");
}

/* typical used to get faulting address when page fault */
static inline uintptr read_cr2(void)
{
    uintptr out;
    asmv("mov %%cr2, %0" : "=a"(out));
    return (out);
}

/* memory specification */
static inline uintptr read_cr4(void)
{
    uintptr out;
    asmv("mov %%cr4, %0" : "=a"(out));
    return (out);
}

static inline void write_cr4(uintptr cr4)
{
    asmv("mov %0, %%cr4" :: "r"(cr4));
}

/* containing the PAGE MAX LVL of pagination */
static inline uintptr read_cr3(void)
{
    uintptr out;
    asmv("mov %%cr3, %0" : "=a"(out));
    return (out);
}

static inline void write_cr3(uintptr cr3)
{
    asmv("mov %0, %%cr3" :: "r"(cr3));
}

static inline void enable_paging(void)
{
    uintptr value;

    asmv("mov %%cr0, %0" : "=a"(value));
    /* bit PG (31) = 1 */
    value |= 0b10000000000000000000000000000000;
    asmv("mov %0, %%cr0" :: "r"(value));
}

static inline void disable_paging(void)
{
    uintptr value;

    asmv("mov %%cr0, %0" : "=a"(value));
    /* bit PG (31) = 0 */
    value &= 0b01111111111111111111111111111111;
    asmv("mov %0, %%cr0" :: "r"(value));
}

#endif
