#include "eternity.h"
#include "threads.h"
#include "pic.h"

extern struct threadDescriptor *threadRunning;

void contextSwitch(struct cpuContext *new)
{
    struct cpuContext *context = getCpuContext();
    memcpy((void *)context, (void *)new, sizeof(struct cpuContext));

    threadDump(threadRunning);
    // cpuContextDump(context);

    cli();
    pic_eoi(IRQ0);
    cli();
    // user_contextSwitch(context);
    kernel_contextSwitch(context);
}