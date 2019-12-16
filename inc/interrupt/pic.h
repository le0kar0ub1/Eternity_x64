#include "eternity.h"

#ifndef _PIC_H_
#define _PIC_H_

void remap_PIC(void);
void pic_outb(uchar port, uchar data);

/* PIC int and shift */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28

#define IRQ0  0x0 // timer
#define IRQ1  0x1 // keyboard
#define IRQ2  0x2 // cascade PIC
#define IRQ3  0x3 // COM2
#define IRQ4  0x4 // COM1
#define IRQ5  0x5 // LPT2
#define IRQ6  0x6 // Floppy disk
#define IRQ7  0x7 // LTP1
#define IRQ8  0x8 // CMOS real-time clock
#define IRQ9  0x9 // Free for peripherals (SCSI / NIC)
#define IRQ10 0xA // Free for peripherals (SCSI / NIC)
#define IRQ11 0xB // Free for peripherals (SCSI / NIC)
#define IRQ12 0xC // PS2 MOUSE
#define IRQ13 0xD // FPU (Floating Point Unit) / Coprocessor / inter-processor
#define IRQ14 0xE // Primary ATA hard disk
#define IRQ15 0xF // Secondary ATA hard disk

/* END OF INTERRUPT */
#define PIC_EOI 0x20 /* data end of interrupt */
static inline void pic_eoi(uchar irq)
{
    if(irq > 0x8)
        outb(PORT_PIC_SLAVE_CMD, PIC_EOI);
    outb(PORT_PIC_MASTER_CMD, PIC_EOI);
}

static inline void io_delay(void)
{
    asmv("outb %%al, $0x80" : : "a"(0));
}

static inline void pic_mask(uchar irq)
{
    /* Get current master PIC interrupt mask */
    uchar curmask_master = inb(PORT_PIC_SLAVE_DATA);
    /* if bit == 0 irq is enable*/
    outb(PORT_PIC_MASTER_DATA, curmask_master | (1 << irq));
}

static inline void pic_unmask(uchar irq)
{
    /* Get current master PIC interrupt mask */
    uchar curmask_master = inb(PORT_PIC_MASTER_DATA);
    /* if bit == 0 irq is enable*/
    outb(PORT_PIC_MASTER_DATA, curmask_master & ~(1 << irq));
}

#endif
