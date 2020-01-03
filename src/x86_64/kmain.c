#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"
#include "descriptors.h"

void init_tty(void);
void fire_userspace(void *stack);
void init_threads(void);

void test(void)
{
    while (1);
    kprint("INSIDE THREAD\n");
    while (1);
}

void kmain(void)
{
    sti();
    // cli();
    void *stack = kalloc(0x6000);
    fire_userspace(stack);
    while (1);
    hlt();

    // init_tty();
    init_threads();
    generateThread_fromRoutine(test, "kernel thread");
    kprint("OUTSIDE THREAD\n");
    while (1) hlt();
}
