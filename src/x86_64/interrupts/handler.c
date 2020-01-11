#include "eternity.h"
#include "interrupt.h"

void (*int_handler[256])(struct frame *);

void init_handler(void)
{
    memsetq(int_handler, 0x0, 0x100); // memset all to 0
}

/* used to register known particular interrupt handler to overhead default */
void register_int_handler(int inbr, void *fnct)
{
    int_handler[inbr] = fnct;
}

void unregister_int_handler(int inbr)
{
    if (inbr > 0x1F)
        return;
    int_handler[inbr] = NULL;
}

void interrupts_handler(struct frame *frame)
{
    if (int_handler[frame->int_num])
        (int_handler[frame->int_num])(frame);
    else
        exceptions_handler(frame);
}
