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


void syscall_enable(void);
void kmain(void)
{
    // sti();
    void *stack = kalloc(0x2000);
    kprint("IN KMAIN\n");
    fire_userspace(stack);
    while (1);
    hlt();

    // init_threads();
    // init_tty();
    // generateThread_fromRoutine(test, "Userspace thread");
    kprint("OUTSIDE THREAD\n");
    while (1) hlt();
}
