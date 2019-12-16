#include "cursor.h"
#include "ports.h"
#include "vga.h"

void enable_cursor(uint8 cursor_start, uint8 cursor_end)
{
    outb(CRTC_INDEX, 0x0A);
    outb(CRTC_DATA, (inb(CRTC_DATA) & 0xC0) | cursor_start);

    outb(CRTC_INDEX, 0x0B);
    outb(CRTC_DATA, (inb(CRTC_DATA) & 0xE0) | cursor_end);
}

void disable_cursor(void)
{
    outb(CRTC_INDEX, 0x0A);
    outb(CRTC_DATA, 0x20);
}

void mov_cursor(int x, int y)
{
    uint16 pos = y * VGA_WIDTH + x;

    outb(CRTC_INDEX, 0x0F);
    outb(CRTC_DATA, (uint8) (pos & 0xFF));
    outb(CRTC_INDEX, 0x0E);
    outb(CRTC_DATA, (uint8) ((pos >> 0x8) & 0xFF));
}

uint16 get_cursor_position(void)
{
    uint16 pos = 0x0;

    outb(CRTC_INDEX, 0x0F);
    pos |= inb(CRTC_DATA);
    outb(CRTC_INDEX, 0x0E);
    pos |= ((uint16)inb(CRTC_DATA)) << 0x8;
    return (pos);
}
