#include "eternity.h"
#include "keyboard.h"
#include "cursor.h"

static inline void prompt(void)
{
    kprint(PROMPT);
}

void init_tty(void)
{
    vga_set_attrib(VGA_RED, VGA_BLACK);
    kprint("\n\n                          PRESS ANY KEY TO LAUCH TTY");
    vga_set_attrib(VGA_WHITE, VGA_BLACK);
    while (read_scan_code() == KEYBOARD_PORT_EMPTY);
    vga_clear();
    // mov_cursor(VGA_WIDTH, VGA_HEIGHT);
    // synchron_cursor_vga(VGA_WIDTH, VGA_HEIGHT - 0x1);
    prompt();
}

void fire_cmd_line(char *buffer)
{
    if (strcmp(buffer, "hello"))
        kprint("Enter in emergency mode\n");
    prompt();
}
