#include "vga.h"

static struct vga vga =
{
    .attrib = 0x0, // font
    .buff = VGA_BUFFER_ADDRESS,
    .posx = 0X0,
    .posy = 0x0,
};

/* synchronisation cursor and pos in vga buffer */
void synchron_cursor_vga(int posx, int posy)
{
    vga.posx = posx;
    vga.posy = posy;
}

/* return the current position in the vga buffer */
void give_cur_pos(int *posx, int *posy)
{
    *posx = vga.posx;
    *posy = vga.posy;
}

void vga_putstr(char const *str)
{
    for (int i = 0x0; str[i]; i++)
        vga_putchar(str[i]);
}

void replace_on_backspace(void)
{
    vga.posy -= 0x1;
    vga.posx = VGA_WIDTH - 0x2;
    intptr index = vgaIndex(vga.posy, vga.posx);

    while (vga.buff[index] == vgaFont(0x20, 0xf) && vga.posx > 0x0) {
        vga.posx -= 0x1;
        index = vgaIndex(vga.posy, vga.posx);
    }
}

void vga_putchar(char c)
{
    const intptr index = vgaIndex(vga.posy, vga.posx);

    switch (c) {
        case 0xA: /* new line */
            if (vga.posy < VGA_HEIGHT - 1) {
                vga.posy += 0x1;
                vga.posx = 0x0;
            }
            break;
        case 0x9: /* tabulation */
            vga.posx += 0x4;
            break;
        case 0x8: /* backspace */
            if (vga.posx == 0x0 && vga.posy == 0x0)
                break;
            if (vga.posx == 0x0 && vga.posy != 0x0)
                replace_on_backspace();
            else {
                vga.buff[index - 0x1] = vgaFont(0x20, vga.attrib);
                vga.posx -= 0x2;
            }
            break;
        case 0xD: /* cariage return */
            vga.posx = 0X0;
            break;
        default:
            vga.buff[index] = vgaFont(c, vga.attrib);
    }
    if (c == 0xA || c == 0xD)
        vga.posx--;
    if (++vga.posx == VGA_WIDTH) {
        vga.posx = 0x0;
        if (++vga.posy == VGA_HEIGHT)
            vga.posy = 0x0;
    }
    mov_cursor(vga.posx, vga.posy);
}

/* mov ptr in the vga buffer */
void movptr_vgabuff(int x, int y)
{
    for (; x > 0x0; x--)
        vga.posx++;
    for (; y > 0x0; y--)
        vga.posy++;
    if (vga.posx >= VGA_WIDTH)
        vga.posx = 0x0;
    if (vga.posy >= VGA_HEIGHT)
        vga.posy = 0x0;
    mov_cursor(vga.posx, vga.posy);
}

void reset_vga_buff(void)
{
    // memsetw(VGA_BUFFER_ADDRESS, vgaFont(0x20, DEFAULT_COLOR), WIDTH * HEIGHT / 2);
    movptr_vgabuff(vga.posx, vga.posy);
}

/* inline function describe in vga.h use to set color */
// uint8 vga_return_color($write, $background)
void vga_set_color(int fg, int bg)
{
    vga.attrib = vga_return_color(fg, bg);
}

void init_vga(void)
{
    vga.attrib = vga_return_color(VGA_WHITE, VGA_BLACK);
    for (intptr y = 0x0; y < VGA_HEIGHT; y++) {
        for (intptr x = 0X0; x < VGA_WIDTH; x++) {
            const intptr index = y * VGA_WIDTH + x;
            vga.buff[index] = vgaFont(0x20, vga.attrib);
        }
    }
}
