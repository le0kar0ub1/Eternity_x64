#ifndef _VGA_DRIVER_H
#define _VGA_DRIVER_H

#include "eternity.h"
#include "cursor.h"

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

extern uint64 __KERNEL_VIRT_BASE;
#define VGA_BUFFER_ADDRESS ((uint16 *)(0xB8000 + &__KERNEL_VIRT_BASE))
// #define VGA_BUFFER_ADDRESS ((uint16 *)(0xB8000))

/* struct use to managing vga */
struct vga
{
    uint8  attrib; // AKA the color
    uint16 *buff;  // located at physical address 0xB8000
    uint   posx;   // current pos in vga buffer x
    uint   posy;   // current pos in vga buffer y
};

// https://en.wikipedia.org/wiki/Enumerated_type enum info
/* VGA init with 0x10 colors */
enum vga_color
{
    VGA_BLACK       = 0x0,
    VGA_BLUE        = 0x1,
    VGA_GREEN       = 0x2,
    VGA_CYAN        = 0x3,
    VGA_RED         = 0x4,
    VGA_PINK        = 0x5,
    VGA_BROWN       = 0x6,
    VGA_LIGHT_GREY  = 0x7,
    VGA_DARK_GREY   = 0x8,
    VGA_LIGHT_BLUE  = 0x9,
    VGA_LIGHT_GREEN = 0xA,
    VGA_LIGHT_CYAN  = 0xB,
    VGA_LIGHT_RED   = 0xC,
    VGA_LIGHT_PINK  = 0xD,
    VGA_YELLOW      = 0xE,
    VGA_WHITE       = 0xF
};

/* Use fonction to VGA to manage screen */
void synchron_cursor_vga(int posx, int posy);
void give_cur_pos(int *posx, int *posy);
void vga_putstr(char const *str);
void vga_putchar(char c);
void movptr_vgabuff(int x, int y);
void vga_clear(void);
void init_vga(void);
void vga_set_attrib(int fg, int bg);
void scroll(void);

/* change color write and background (in order) */
static inline uint8 vga_attrib(enum vga_color fg, enum vga_color bg)
{
    return (fg | bg << 0x4);
}

/* modify the vga buffer */
static inline uint16 vgaFont(uchar uc, uint8 color)
{
    return ((uint16) uc | (uint16) color << 0x8);
}

static inline intptr vgaIndex(uint posy, uint posx)
{
    return (posy * VGA_WIDTH + posx);
}

static inline intptr vgaGetPixel(uint posy, uint posx)
{
    return (VGA_BUFFER_ADDRESS[posy * VGA_WIDTH + posx]);
}

#endif
