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

#define asmv __asm__ volatile
#define syscall int 0x80
#define KERNEL_VIRT_LINK  0xFFFFFFFF80100000

void PANIC(char const *panic);

#endif
