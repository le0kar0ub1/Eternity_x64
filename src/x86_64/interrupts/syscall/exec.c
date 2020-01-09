#include "eternity.h"
#include "threads.h"

int syscall_exec(void *routine, char *name)
{
    generateThread_fromRoutine(routine, name);
    return (0x0);
}