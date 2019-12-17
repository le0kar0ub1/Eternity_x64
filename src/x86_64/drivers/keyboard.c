#include "keyboard.h"
#include "pic.h"

/* Scan code set for azerty keyboard */
/* struct keys handle by the kernel driver */

static uchar const azerty_keyset[128] =
{
    0,
    [2] = '&',
    [4] = '\"',
    [5] = '\'',
    [6] = '(',
    [7] = '-',
    [9] = '_',
    [12] = ')',
    [13] = '=',
    [16] = 'a',
    [17] = 'z',
    [18] = 'e',
    [19] = 'r',
    [20] = 't',
    [21] = 'y',
    [22] = 'u',
    [23] = 'i',
    [24] = 'o',
    [25] = 'p',
    [30] = 'q',
    [31] = 's',
    [32] = 'd',
    [33] = 'f',
    [34] = 'g',
    [35] = 'h',
    [36] = 'j',
    [37] = 'k',
    [38] = 'l',
    [39] = 'm',
    [44] = 'w',
    [45] = 'x',
    [46] = 'c',
    [47] = 'v',
    [48] = 'b',
    [49] = 'n',
    [28] = '\n',
    [14] = '\b',
    [50] = ',',
    [51] = ';',
    [52] = ':',
    [53] = '!',
    [57] = ' ',
    [27] = '$',
    [43] = '*',
    [26] = '^'
};

static uchar const azerty_keyset_altgr[128] =
{
    0,
    [2] = '&',
    [3] = '~',
    [4] = '#',
    [5] = '{',
    [6] = '[',
    [9] = '\\',
    [11] = '@',
    [12] = ']',
    [13] = '}',
    [16] = 'a',
    [17] = 'z',
    [18] = 'e',
    [19] = 'r',
    [20] = 't',
    [21] = 'y',
    [22] = 'u',
    [23] = 'i',
    [24] = 'o',
    [25] = 'p',
    [30] = 'q',
    [31] = 's',
    [32] = 'd',
    [33] = 'f',
    [34] = 'g',
    [35] = 'h',
    [36] = 'j',
    [37] = 'k',
    [38] = 'l',
    [39] = 'm',
    [44] = 'w',
    [45] = 'x',
    [46] = 'c',
    [47] = 'v',
    [48] = 'b',
    [49] = 'n',
    [28] = '\n',
    [14] = '\b',
    [50] = ',',
    [51] = ';',
    [57] = ' '
};

static uchar const azerty_keyset_capslock[128] =
{
    0,
    [2] = '1',
    [3] = '2',
    [4] = '3',
    [5] = '4',
    [6] = '5',
    [7] = '6',
    [8] = '7',
    [9] = '8',
    [10] = '9',
    [11] = '0',
    [13] = '+',
    [16] = 'A',
    [17] = 'Z',
    [18] = 'E',
    [19] = 'R',
    [20] = 'T',
    [21] = 'Y',
    [22] = 'U',
    [23] = 'I',
    [24] = 'O',
    [25] = 'P',
    [30] = 'Q',
    [31] = 'S',
    [32] = 'D',
    [33] = 'F',
    [34] = 'G',
    [35] = 'H',
    [36] = 'J',
    [37] = 'K',
    [38] = 'L',
    [39] = 'M',
    [44] = 'W',
    [45] = 'X',
    [46] = 'C',
    [47] = 'V',
    [48] = 'B',
    [49] = 'N',
    [28] = '\n',
    [14] = '\b',
    [50] = '?',
    [51] = '.',
    [52] = '/',
    [57] = ' ',
    [40] = '%'
};


static bool caps_lock = false;
static bool caps = false;
static bool ctrl = false;
static bool altgr = false;
static int color = 0xF;

// void key_arrow_pressed(uchar getch)
// {
//     int posx = 0x0, posy = 0x0;
//
//     give_cur_pos(&posx, &posy);
//     if (getch == 75 && posx > 0) { // Left arrow
//         posx--;
//         mov_cursor(posx, posy);
//     }
//     else if (getch == 72 && posy > 0) {
//         posy--;
//         mov_cursor(posx, posy);
//     }
//     else if (getch == 80 && posy < 24) {
//         posy++;
//         mov_cursor(posx, posy);
//     }
//     else if (getch == 77 && posx < 79) {
//         posx++;
//         mov_cursor(posx, posy);
//     }
//     synchron_cursor_vga(posx, posy);
// }

void classic_char_print(struct frame *frame, uchar getch)
{
    if (caps_lock != caps)
        frame->rax = azerty_keyset_capslock[getch];
    else if (altgr && !caps_lock && !caps)
        frame->rax = azerty_keyset_altgr[getch];
    else
        frame->rax = azerty_keyset[getch];
    /* print on screen */
    if (frame->rax != 0x0)
        kprint("%c", frame->rax);
}


void special_int_trig(uchar getch)
{
    if (getch == 0x2A || getch == 0x36) // caps on
        caps = true;
    if (getch == 170 || getch == 182) // caps release
        caps = false;
    if (getch == 0x1D) // ctrl on
        ctrl = true;
    if (getch == 157) // ctrl release
        ctrl = false;
    if (getch == 0x3A) // caps_lock is touch
        caps_lock = !caps_lock;
    if (getch == 0xE0)
        altgr = !altgr;
    if (getch == 0x29) { // "²" touch use for set color
        color = (color > 0xE) ? 0x0 : color + 1;
        vga_set_attrib(color, VGA_BLACK);
    }
}

uchar read_scan_code(void)
{
    return (inb(PORT_PS2_KEYBOARD_CMD));
}

void keyboard_handler(struct frame *frame)
{
    uchar getch = read_scan_code();

    if (getch < 60 && (azerty_keyset[getch] ||
azerty_keyset_altgr[getch] ||  azerty_keyset_capslock[getch]))
        classic_char_print(frame, getch);
    else
        special_int_trig(getch);
    // else if (getch == 75 || getch == 72 || getch == 80 || getch == 77)
    //     key_arrow_pressed(getch);
    pic_eoi(IRQ1);
}


void init_keyboard(void)
{
    /* register handler */
    register_int_handler(INT_IRQ1, keyboard_handler);
    /* unmask IRQ1 aka the keyboard */
    pic_unmask(IRQ1);
}
