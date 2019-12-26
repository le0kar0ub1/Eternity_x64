#include "eternity.h"
#include "interrupt.h"

char const *exception_message[MAX_INT] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor (not available)",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS", // Task State Segment
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt (reserved)",
    "Coprocessor (FPE) Fault",
    "Alignment Check",
    "Machine Check",
    "SIMD (FPE)",
    "Virtualization exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security exception",
    "Reserved",
    "Reserved"
};

void PANIC(char const *panic, ...)
{
    va_list ap;

    cli();
    va_start(ap, panic);
    vga_set_attrib(VGA_RED, VGA_BLACK);
    kvprint(panic, ap);
    va_end(ap);
    while (1) hlt();
}

void exceptions_handler(uintptr int_num)
{
    /* if this is not an exception, kick it */
    if (int_num > 0x1F)
        return;
    vga_set_attrib(VGA_RED, VGA_BLACK);
    /* Kernel panic, reboot progress... */
    kprint("Internal Panic: %s\n", exception_message[int_num]);
    cli();
    hlt();
}
