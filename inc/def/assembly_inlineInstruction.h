#ifndef _ASSEMBLY_INLINE_INSTRUCTION_H_
#define _ASSEMBLY_INLINE_INSTRUCTION_H_

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

    asm volatile("lock xchgl %0, %1;" : "+m"(*addr), "=a"(res) : "1"(newval) : "cc");
    return (res);
}

static inline uint32 get_eflags(void)
{
    uint32 e;

    asm volatile("pushfl; popl %0" : "=rm"(e) :: "memory");
    return (e);
}

static inline void set_eflags(uint32 value)
{
    asm volatile("pushl %0; popfl" :: "g"(value) : "memory", "cc");
}

#endif
