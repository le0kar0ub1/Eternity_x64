#ifndef _ETERNITY_H_
#define _ETERNITY_H_

/* basic headers library */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
/* recreate headers library */
#include "prototypes.h"

/* MACRO AND DEF HELPER */
#include "typedef.h"
#include "eternityDef.h"
#include "compare.h"

/* personnal headers */
#include "vga.h"
#include "bitfield.h"
#include "assembly_inlineInstruction.h"
#include "memory.h"
#include "tty.h"
#include "kconfig.h"

/* Kernel Panic */
void PANIC(char const *panic, ...) __noreturn;
/* Kernel main  */
void kmain(void) __noreturn;

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
