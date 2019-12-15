#ifndef _BLACKOUT_H_
#define _BLACKOUT_H_

/* basic headers library */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/* recreate headers library */
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

/* personnal headers */
#include "types_shortcut.h"
#include "macro.h"
#include "vga.h"
#include "bitfield.h"

#define asmv __asm__ volatile
#define printk printf
#define syscall int 0x80
#define clear reset_vga_buff
#define DEBUG while (0b1) hlt();

void PANIC(char const *panic);

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
