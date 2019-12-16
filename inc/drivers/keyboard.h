#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

#include "eternity.h"
#include "ports.h"
#include "interrupt.h"

void init_keyboard(void);
uchar read_scan_code(void);

/* define some keys and values to set keyboard */
// #define KEYBOARD_MAX_RETRY         10000
// #define SC1_CAPSLOCK_PRESSED       0x3A
//
// #define KEYBOARD_ACK               0xFA
// #define KEYBOARD_RESEND            0xFE
//
// #define KEYBOARD_CMD_SCANCODE      0xF0
// #define KEYBOARD_CMD_LED           0xED
//
// #define KEYBOARD_SCANCODE_GET      0x00
// #define KEYBOARD_SCANCODE_SET_1    0x01
// #define KEYBOARD_SCANCODE_SET_2    0x02
// #define KEYBOARD_SCANCODE_SET_3    0x03
//
// #define KEYBOARD_STATUS_RDOK       (1 << 0)
// #define KEYBOARD_STATUS_WRNOTOK    (1 << 1)

#endif
