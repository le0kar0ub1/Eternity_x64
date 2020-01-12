#ifndef _ASSEMBLY_INLINE_INSTRUCTION_H_
#define _ASSEMBLY_INLINE_INSTRUCTION_H_

#include "stdint.h"

#define asmv __asm__ volatile

/* nbr of cpu ticks from last reset */
static inline uint64 rdtsc(void)
{
    uint64 ret;
    asmv("rdtsc" : "=A"(ret));
    return (ret);
}

/* wait an interrupt */
static inline void hlt(void)
{
    asmv("hlt");
}

/* pushfq/popfq instruction*/
static inline void pushfq(void)
{
    asmv("pushfq");
}

static inline void popfq(void)
{
    asmv("popfq");
}

/* enable interruption */
static inline void sti(void)
{
    asmv("sti");
}

/* disable interruption */
static inline void cli(void)
{
    asmv("cli");
}

/* enable direction flag */
static inline void std(void)
{
    asmv("std");
}

/* disable direction flag */
static inline void cld(void)
{
    asmv("cld");
}


/* force a thread to sleep */
static inline void pause(void)
{
    asmv("pause");
}

/* fire an interrupt */
static inline void interrupt(uchar vector)
{
    asmv("int %0" :: "i"(vector));
}

static inline uint xchg(uint volatile *addr, uint newval)
{
    uint res;

    asmv("lock xchgl %0, %1;" : "+m"(*addr), "=a"(res) : "1"(newval) : "cc");
    return (res);
}

static inline uint64 get_rflags(void)
{
    uint64 e;

    asmv("pushfq; pop %0" : "=rm"(e) :: "memory");
    return (e);
}

static inline void set_rflags(uint64 value)
{
    asmv("push %0; popfq" :: "g"(value) : "memory", "cc");
}

static inline uint64 read_rflags(void)
{
    return (__builtin_ia32_readeflags_u64());
}

static inline void write_rflags(uint64 rflags)
{
    __builtin_ia32_writeeflags_u64(rflags);
}

static inline void preempt_inc(void)
{
    asmv("lock incl %%gs:0x18" :: );
}

static inline void preempt_dec(void)
{
    asmv("lock decl %%gs:0x18" :: );
}

#endif
