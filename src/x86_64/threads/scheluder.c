#include "scheluder.h"
#include "threads.h"

extern list_t *threadList;

struct threadDescriptor *threadRunning = NULL;

struct cpuContext savedContext;

struct cpuContext *getCpuContext(void)
{
    return (&savedContext);
}

/* Dumb scheluder */
void threadScheluder(void)
{
    if (!list_size(threadList))
        return;
    if (!threadRunning) {
        threadRunning = list_peek_front(threadList);
        goto switchExec;
    }
    /* Remove Zombie thread */
    if (threadRunning->state == THREAD_ZOMBIE)
        list_remove_node(threadList, threadRunning->listIdx);
    /* or save the cpu context inside the thread context */
    else
        memcpy((void *)&(threadRunning->context), (void *)&savedContext, sizeof(struct cpuContext));
    
    if (!((threadRunning->listIdx)->next))
        threadRunning = list_peek_front(threadList); // cycle from start
    else
        threadRunning = (threadRunning->listIdx)->next->item; // next thread
    /* if all thread have been exited then crash... */
    fatalAssert(threadRunning);

/* do the context switch */
switchExec:
    contextSwitch(&threadRunning->context);
}