#include "eternity.h"
#include "threads.h"
#include "pic.h"

extern struct threadDescriptor *threadRunning;

void contextSwitch(struct cpuState *new)
{
    struct cpuState *context = getCpuContext();
    memcpy((void *)context, (void *)new, sizeof(struct cpuState));
    /*                          */
    /* HERE COME THE CR3 SWITCH */
    /*                          */
    // user_contextSwitch(context);
    pic_eoi(0x0);
    kernel_contextSwitch(context);
}