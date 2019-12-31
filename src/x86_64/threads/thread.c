#include "processus.h"
#include "interrupt.h"
#include "timer.h"

extern list_t *threadList;

pid_t new_pid(void)
{
    static pid_t processId = 0x0;
    processId += 0x1;
    return (processId);
}

void generateThread(char *file)
{
    struct threadDescriptor *thread = kalloc(sizeof(struct threadDescriptor));

    // thread file name
    strcpy(thread->name, file);
    // context set up
    memset((void *)(&(thread->context)), 0x0, sizeof(struct context));
    thread->context.rip = 0x0; // (uint64)load_elf
    thread->context.eflags = 0x206; // interruptible
    thread->idx = list_insert_front(threadList, thread);
    // thread memory set up
    thread->stack = kalloc(0x1000 * 0x10);
    thread->context.rsp = (uint64)thread->stack - (0x1000);
    
    /**/
    /* HERE COME THE CR3 PAGE DIRECTORY SWITCH */
    /**/

    thread->state = THREAD_CREATED;
}

void init_process(void)
{
    threadList = list_create();
    register_functionWakeup(threadScheluder, 10); // subscribe a sheluder call all 0.1 sec
}