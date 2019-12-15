#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "blackout.h"
#include "multiboot2.h"
#include "paging.h"
/* https://os.phil-opp.com/paging-introduction/ */
/* http://www.jamesmolloy.co.uk/tutorial_html/6.-Paging.html */

#define INDEX_FROM_BIT(b)  (b / (0x8 * 0x20))
#define OFFSET_FROM_BIT(b) (b % (0x8 * 0x20))

typedef uintptr physaddr_t;
typedef void    *virtaddr_t;

extern uint64 KERNEL_END;

/* VIRTUAL PAGE BITS SETTINGS */
#define PE  0x0
#define MP  0x1
#define EM  0x2
#define TS  0x3
#define ET  0x4
#define NE  0x5
#define WP  0x10
#define AM  0x12
#define PG  0x1F

#define K 0x400
#define M (0x400 * K)
#define G (0x400 * M)

#define LOAD_MEM_ADDR       0x100000
#define PHYS_MM_START_USED  (PAGE_ALIGN((uint64)&KERNEL_END))

/* paging memory */
void identity_mapp(void);
void map_memory(ulong addr);

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
