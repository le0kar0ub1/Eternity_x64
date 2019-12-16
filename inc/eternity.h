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
// #include "vga.h"
#include "bitfield.h"
#include "assembly_inlineInstruction.h"

#define asmv __asm__ volatile
#define printk printf
#define syscall int 0x80
#define clear reset_vga_buff
#define DEBUG while (0b1) hlt();

void PANIC(char const *panic);

#endif
