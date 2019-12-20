#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "eternity.h"
// #include "paging.h"
/* https://os.phil-opp.com/paging-introduction/ */
/* http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html */

extern uint64 __KERNEL_VIRT_BASE;
extern uint64 __KERNEL_VIRT_LINK;
extern uint64 __KERNEL_VIRT_END;
extern uint64 __KERNEL_PHYS_START;
extern uint64 __KERNEL_PHYS_END;

/* page define at boot are accessed with translation */
#define V2P(x) ((uint64)x - (uint64)(&__KERNEL_VIRT_BASE))
#define P2V(x) ((uint64)x + (uint64)(&__KERNEL_VIRT_BASE))

typedef uintptr physaddr;
typedef void    *virtaddr;

#define K 0x400
#define M (0x400 * K)
#define G (0x400 * M)

#define LOAD_PHYS_ADDR      (&__KERNEL_PHYS_START)
#define LOAD_VIRT_ADDR      (&__KERNEL_VIRT_LINK)
#define PHYS_MM_START_USED  (PAGE_ALIGN((uint64)&__KERNEL_PHYS_END))

/* paging memory */
void identity_mapp(void);
void map_memory(ulong addr);
void *fromIndexToAdrr(uint64 pml4, uint64 pdpt, uint64 pdt, uint64 pt);

/* invalid a page of TLB (TLB increase speed if addr was already page) */
static inline void invlpg(void *addr)
{
    asmv("invlpg (%0)" :: "r"(addr) : "memory");
}

/* typical used to get faulting address when page fault */
static inline uintptr read_cr2(void)
{
    uintptr out;
    asmv("mov %%cr3, %0" : "=a"(out));
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
