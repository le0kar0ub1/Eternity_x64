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

#define asmv __asm__ volatile
#define syscall int 0x80

void PANIC(char const *panic);
void kmain(void);

#endif
