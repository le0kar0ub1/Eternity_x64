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
    void *stack = kalloc(0x2000);
    sti();
    while (1);
    fire_userspace(stack);

    // init_threads();
    // init_tty();
    // generateThread_fromRoutine(test, "Userspace thread");
    kprint("OUTSIDE THREAD\n");
    while (1) hlt();
}
