#include "eternity.h"
#include "interrupt.h"

void (*int_handler[256])(struct frame *);

void init_handler(void)
{
    memset(int_handler, 0x0, 0x100 * 0x8); // memset all to 0
}

/* used to register known particular interrupt handler to overhead default */
void register_int_handler(int nbr, void *fnct)
{
    int_handler[nbr] = fnct;
}

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


void interrupts_handler(struct frame *frame)
{
    if (int_handler[frame->int_num])
        (int_handler[frame->int_num])(frame);
    hlt();
}
