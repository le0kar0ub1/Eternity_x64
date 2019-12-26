#ifndef _ETERNITY_H_
#define _ETERNITY_H_

/* basic headers library */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/* recreate headers library */
#include "prototypes.h"

/* personnal headers */
#include "types_shortcut.h"
#include "macro.h"
#include "vga.h"
#include "bitfield.h"
#include "assembly_inlineInstruction.h"
#include "memory.h"
#include "tty.h"
#include "kconfig.h"

#define asmv __asm__ volatile
#define syscall int 0x80

void PANIC(char const *panic);
void kmain(void);
void *kalloc(uint size);
void kfree(void *ptr);

/* facilities */
static inline void debug(uint64 arg)
{
    kprint("debug address: %x\n", arg);
    hlt();
}

static inline void fromCstToWr(char const *s, char *new)
{
    uint i = 0x0;

    for (; s[i]; i++)
        new[i] = s[i];
}

#endif
