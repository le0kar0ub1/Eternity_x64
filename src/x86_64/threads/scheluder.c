#include "scheluder.h"
#include "threads.h"

extern list_t *threadList;

struct threadDescriptor *threadRunning = NULL;

struct cpuState savedContext;

struct cpuState *getCpuContext(void)
{
    return (&savedContext);
}

void threadScheluder(void)
{
    if (!list_size(threadList))
        return;
    if (!threadRunning) {
        threadRunning = list_peek_front(threadList);
        threadDump(threadRunning);
        goto switchExec;
    }
    /* Remove Zombie thread */
    if (threadRunning->state == THREAD_ZOMBIE)
        list_remove_node(threadList, threadRunning->listIdx);
    
    if (!(threadRunning->listIdx->next))
        threadRunning = list_peek_front(threadList); // cycle from start
    else
        threadRunning = threadRunning->listIdx->next->item; // next thread
    threadDump(threadRunning);
    /* of all thread exited then crash... */
    if (!threadRunning)
        PANIC("No thread left, userspace crashed...\n");

/* do the context switch */
switchExec:
    contextSwitch(&threadRunning->context);
}