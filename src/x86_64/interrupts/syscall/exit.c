#include "eternity.h"
#include "threads.h"

extern struct threadDescriptor *threadRunning;

void syscall_exit(int status)
{
    /* syscall exit just set the current thread as ZOMBIE */
    threadRunning->state = THREAD_ZOMBIE;
    threadRunning->lifeCycle = status;
    /* then call the scheluder to kill the thread */
    threadScheluder();
}