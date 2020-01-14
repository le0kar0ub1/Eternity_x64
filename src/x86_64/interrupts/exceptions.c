#include "eternity.h"
#include "interrupt.h"
#include "cpuContext.h"
#include "threads.h"
#include "ports.h"
#include "pic.h"

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

void exceptions_handler(struct frame *frame)
{
    /* if this is not an exception, kick it */
    if (frame->int_num > 0x1F)
        return;
    cli();
    vga_set_attrib(VGA_RED, VGA_BLACK);
    /* Kernel panic, reboot progress... */
    kprint("\nKernel Panic: %s\n", exception_message[frame->int_num]);
    kprint("yayayaya %l\n", (uint64)frame->rax);
    hlt();
    while(1);
    cpuContextDump((struct cpuContext *)frame);
    vga_set_attrib(VGA_WHITE, VGA_BLACK);
    serial_kprint("Faulting address: %x\n", frame->rip);
}
