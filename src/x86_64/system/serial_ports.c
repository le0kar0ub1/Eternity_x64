#include "interrupt.h"
#include "ports.h"
#include "stdarg.h"

int serial_received(void)
{
    return inb(COM1 + 5) & 1;
}

char read_serial(void)
{
    while (serial_received() == 0);
    return inb(COM1);
}

int is_transmit_empty(void)
{
    return inb(COM1 + 5) & 0x20;
}

/* WRITE ON QEMU LOGS */
void write_serial(char a)
{
    while (is_transmit_empty() == 0);
    outb(COM1,a);
}

void serial_putstr(char *s)
{
    for (int i = 0x0; s[i]; i++)
        write_serial(s[i]);
}

void init_serial(void) {
    outb(COM1 + 0x1, 0x00);    // Disable all interrupts
    outb(COM1 + 0x3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0x0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 0X1, 0x00);    //                  (hi byte)
    outb(COM1 + 0x3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 0x2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 0X4, 0x0B);    // IRQs enabled, RTS/DSR set
}
