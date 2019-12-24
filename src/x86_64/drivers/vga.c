#include "vga.h"
#include "tty.h"

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
            vga.posx = 0x0;
            if (vga.posy < VGA_HEIGHT - 0x1)
                vga.posy += 0x1;
            else
                scroll();
            break;
        case 0x9: /* tabulation */
            vga.posx += 0x4;
            break;
        case 0x8: /* backspace */
            if ((vga.posx == 0x0 && vga.posy == 0x0) || vga.posx - 0x1 < PROMPTLEN)
                return;
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

void scroll(void) {
    void* start = (void *)VGA_BUFFER_ADDRESS + (1 * VGA_WIDTH * 2);
    uint32_t size = vga.posy * VGA_WIDTH * 2;

    if(vga.posy < VGA_HEIGHT - 0x1)
        return;
    memcpy(VGA_BUFFER_ADDRESS, start, size);
    start = (void *)VGA_BUFFER_ADDRESS + size;
    memsetw(start, vgaFont(0x20, vga.attrib), VGA_WIDTH);
}

void vga_clear(void)
{
    memsetd(VGA_BUFFER_ADDRESS, vgaFont(0x20, vga.attrib), VGA_WIDTH * VGA_HEIGHT);
    movptr_vgabuff(vga.posx, vga.posy);
}

/* vga_attrib($write, $background) */
void vga_set_attrib(int fg, int bg)
{
    vga.attrib = vga_attrib(fg, bg);
}

void init_vga(void)
{
    vga_set_attrib(VGA_WHITE, VGA_BLACK);
    vga_clear();
}
