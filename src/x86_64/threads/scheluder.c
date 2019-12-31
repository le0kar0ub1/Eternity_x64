#include "scheluder.h"
#include "processus.h"

struct threadDescriptor *run;
struct threadDescriptor *prev;

struct list_t *threadList;

struct context *savedContext;

void generateThread(char *file)
{
    struct threadDescriptor *thread = kalloc(sizeof(struct threadDescriptor));

    // thread file name
    strcpy(thread->name, file);
    // context set up
    memset((void *)&(thread->context), 0x0, sizeof(struct context));
    thread->context.rip = 0x0; // (uint64)load_elf
    thread->context.eflags = 0x206;
}

void threadScheluder(void)
{
}