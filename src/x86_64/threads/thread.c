#include "threads.h"
#include "interrupt.h"
#include "timer.h"

list_t *threadList;

pid_t new_pid(void)
{
    static pid_t processId = 0x0;
    processId += 0x1;
    return (processId);
}

void threadListDump(void)
{
    listnode_t *dump = threadList->head;
    uint64 listSize = threadList->size;

    if (!dump)
        return;
    kprint("Thread list:\n");
    for (; listSize > 0x1; dump = dump->next, listSize--)
        kprint("    %s\n", ((struct threadDescriptor *)dump->item)->name);
}

void generateThread_fromRoutine(void *function, char const *name)
{
    struct threadDescriptor *thread = kalloc(sizeof(struct threadDescriptor));

    // thread name
    strcpy(thread->name, name);
    thread->pid = new_pid();
    // context set up
    memset((void *)(&(thread->context)), 0x0, sizeof(struct cpuState));
    thread->context.rip = (uint64)function; 
    thread->context.rflags = 0x202; // interruptible
    thread->listIdx = list_insert_front(threadList, thread);
    // thread memory set up
    thread->stack = kalloc(0x1000 * 0x10);
    thread->context.rbp = (uint64)thread->stack;
    thread->context.rsp = (uint64)thread->stack - (0x1000);
    
    /*                                         */
    /* HERE COME THE CR3 PAGE DIRECTORY SWITCH */
    /*                                         */

    /* Some State Variable */
    thread->lifeCycle = LIFECYCLE_DEFAULT;
    thread->state = THREAD_CREATED;
}

void generateThread(char *file)
{
    struct threadDescriptor *thread = kalloc(sizeof(struct threadDescriptor));

    // thread file name
    strcpy(thread->name, file);
    // context set up
    memset((void *)(&(thread->context)), 0x0, sizeof(struct cpuState));
    thread->context.rip = 0x0; // (uint64)load_elf
    thread->context.rflags = 0x206; // interruptible
    thread->listIdx = list_insert_front(threadList, thread);
    // thread memory set up
    thread->stack = kalloc(0x1000 * 0x10);
    thread->context.rsp = (uint64)thread->stack - (0x1000);
    
    /*                                         */
    /* HERE COME THE CR3 PAGE DIRECTORY SWITCH */
    thread->context.cr3 = read_cr3(); // for the moment keep the same PML4
    /*                                         */

    /* Some State Variable */
    thread->lifeCycle = LIFECYCLE_DEFAULT;
    thread->state = THREAD_CREATED;
}

void init_threads(void)
{
    threadList = list_create();
    register_functionWakeup(threadScheluder, 10); // subscribe a sheluder call all 0.1 sec
}