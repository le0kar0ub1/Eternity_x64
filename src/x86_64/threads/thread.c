#include "threads.h"
#include "interrupt.h"
#include "timer.h"
#include "rflags.h"
#include "descriptors.h"

list_t *threadList;

pid_t new_pid(void)
{
    static pid_t processId = 0x0;
    processId += 0x1;
    return (processId);
}

extern struct threadDescriptor *threadRunning;

void setDefaultSegmentContext(struct threadDescriptor *thread)
{
    thread->context.ds = (USER_DATA_SELECTOR | 0x3);
    thread->context.es = (USER_DATA_SELECTOR | 0x3);
    thread->context.fs = (USER_DATA_SELECTOR | 0x3);
    thread->context.gs = (USER_DATA_SELECTOR | 0x3);
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
    thread->context.rflags = 0x286; // Interruptible | Present | Res1 | Carry
    setDefaultSegmentContext(thread);
    // thread memory set up
    uint64 stack = (uint64)kalloc(0x1000 * 0x2);
    thread->context.rbp = stack;
    thread->context.rsp = stack;

    /*                                         */
    /* HERE COME THE CR3 PAGE DIRECTORY SWITCH */
    /*                                         */

    /* Some State Variable */
    thread->lifeCycle = LIFECYCLE_DEFAULT;
    thread->state = THREAD_CREATED;

    /* instanciation */
    thread->listIdx = list_insert_front(threadList, thread);
}

void generateThread(char *file)
{
    struct threadDescriptor *thread = kalloc(sizeof(struct threadDescriptor));

    // thread name
    strcpy(thread->name, file);
    thread->pid = new_pid();
    // context set up
    memset((void *)(&(thread->context)), 0x0, sizeof(struct cpuState));
    thread->context.rip = (uint64)0x0; // ELF_LOADER(file) 
    thread->context.rflags = 0x286; //IF | RES1 | PF; // interruptible
    setDefaultSegmentContext(thread);
    // thread memory set up
    uint64 stack = (uint64)kalloc(0x1000 * 0x2);
    thread->context.rbp = stack;
    thread->context.rsp = stack;

    /*                                         */
    /* HERE COME THE CR3 PAGE DIRECTORY SWITCH */
    /*                                         */

    /* Some State Variable */
    thread->lifeCycle = LIFECYCLE_DEFAULT;
    thread->state = THREAD_CREATED;

    /* instanciation */
    thread->listIdx = list_insert_front(threadList, thread);
}

void init_threads(void)
{
    threadList = list_create();
    register_functionWakeup(threadScheluder, 10); // subscribe a sheluder call all 0.1 sec
}