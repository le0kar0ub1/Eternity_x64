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
    if (!threadRunning)
        threadRunning = list_peek_front(threadList);
    /* Remove Zombie thread */
    if (threadRunning->state == THREAD_ZOMBIE)
        list_remove_node(threadList, threadRunning->listIdx);
    if (!(threadRunning->listIdx->next))
        threadRunning = list_peek_front(threadList); // cycle from start
    else
        threadRunning = threadRunning->listIdx->next->item; // next thread
    if (!threadRunning)
        PANIC("No thread left, userspace crashed...\n");
    contextSwitch(&threadRunning->context);
}