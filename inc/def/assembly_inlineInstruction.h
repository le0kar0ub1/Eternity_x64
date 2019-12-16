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

#endif
