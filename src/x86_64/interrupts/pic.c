#include "eternity.h"
#include "interrupt.h"
#include "ports.h"
#include "pic.h"

void pic_outb(uchar port, uchar data)
{
    outb(port, data);
    io_delay();
}

/* BASIC PIC REMAP */
void init_pic(void)
{
    pic_outb(PORT_PIC_MASTER_CMD, 0x11); // starts the initialization
    pic_outb(PORT_PIC_SLAVE_CMD, 0x11);

    pic_outb(PORT_PIC_MASTER_DATA, INT_IRQ0);      // INT master PIC
    pic_outb(PORT_PIC_SLAVE_DATA, INT_IRQ0 + 0x8); // INT slave PIC

    pic_outb(PORT_PIC_MASTER_DATA, 0x4);
    pic_outb(PORT_PIC_SLAVE_DATA, 0x2);

    pic_outb(PORT_PIC_MASTER_DATA, 0x1);
    pic_outb(PORT_PIC_SLAVE_DATA, 0x1);

    pic_outb(PORT_PIC_MASTER_DATA, 0xFF); // Mask all interrupts
    pic_outb(PORT_PIC_SLAVE_DATA, 0xFF);
}
