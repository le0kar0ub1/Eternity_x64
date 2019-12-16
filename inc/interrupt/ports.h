#ifndef _PORTS_H_
#define _PORTS_H_
// https://wiki.osdev.org/8259_PIC
#include "eternity.h"

/* PORT serial to managing communication */
#define COM1 0x3f8 /* COM1 */
void serial_putstr(char *s);
void write_serial(char a);
char read_serial(void);

/*  A value assign to each ports */
enum port
{
    PORT_PIC_MASTER_CMD      = 0x20,
    PORT_PIC_MASTER_DATA     = 0x21,
    PORT_IMCR_ADDRESS        = 0x22,
    PORT_IMCR_DATA           = 0x23,

    /* PIT PUCE */
    PORT_PIT0_IO             = 0x40,
    PORT_PIT1_IO             = 0x41,
    PORT_PIT2_IO             = 0x42,
    PORT_PIT_CMD_WRONLY      = 0x43,
    PORT_PIT2_HP             = 0x61,

    /* KEYBOARD PORT (also PS2 port) */
    PORT_PS2_KEYBOARD_DATA   = 0x60,
    PORT_PS2_KEYBOARD_CMD    = 0x60,
    PORT_PS2_KEYBOARD_STATUS = 0x64,

    PORT_CMOS                = 0x70,
    PORT_CMOS_RETURN         = 0x71,
    PORT_PIC_SLAVE_CMD       = 0xA0,
    PORT_PIC_SLAVE_DATA      = 0xA1,
};

/* read port (byte) */
static inline uchar inb(ushort port)
{
    uchar ret;
    asmv("inb %1, %0" : "=a"(ret) : "d"(port));
    return (ret);
}

/* read port (word) */
static inline ushort inw(ushort port)
{
    ushort ret;
    asmv("inw %1, %0" : "=a"(ret) : "d"(port));
    return (ret);
}

/* read port (double) */
static inline uint ind(ushort port)
{
    uint ret;
    asmv("inl %1, %0" : "=a"(ret) : "d"(port));
    return (ret);
}

/* write port (byte) */
static inline void outb(ushort port, uchar data)
{
    asmv("outb %0, %1" :: "a"(data), "d"(port));
}

/* write port (word) */
static inline void outw(ushort port, ushort data)
{
    asmv("outw %0, %1" :: "a"(data), "d"(port));
}

/* write port (double) */
static inline void outd(ushort port, uint data)
{
    asmv("outl %0, %1" :: "a"(data), "d"(port));
}

#endif
