#include "eternity.h"
#include "threads.h"
#include "pic.h"

extern struct threadDescriptor *threadRunning;

void contextSwitch(struct cpuState *new)
{
    struct cpuState *context = getCpuContext();
    memcpy((void *)context, (void *)new, sizeof(struct cpuState));

    // threadDump(struct threadDescriptor *thread)
    // cpuContextDump(context);

    pic_eoi(IRQ0);
    // user_contextSwitch(context);
    kernel_contextSwitch(context);
}