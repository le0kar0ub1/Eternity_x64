#include "processus.h"
#include "interrupt.h"
#include "timer.h"

extern struct list_t *threadList;

pid_t new_pid(void)
{
    static pid_t processId = 0x0;
    processId += 0x1;
    return (processId);
}


void init_process(void)
{
    threadList = (struct list_t *)list_create();
    register_functionWakeup(threadScheluder, 10); // subscribe a sheluder call all 0.1 sec
}