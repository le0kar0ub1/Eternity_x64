#include "vga.h"
#include "eternity.h"

#ifndef _CURSOR_DRIVER_H
#define _CURSOR_DRIVER_H

#define CRTC_DATA  0x3D5
#define CRTC_INDEX 0x3D4

/* Use fonction to manage cursor */
void enable_cursor(uint8 cursor_start, uint8 cursor_end);
void disable_cursor(void);
void mov_cursor(int x, int y);
uint16 get_cursor_position(void);

#endif
