#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"

void init_tty(void);
void fire_userspace(void);
void init_threads(void);

void test(void)
{
    while (1);
    kprint("INSIDE THREAD\n");
    while (1);
}

void kmain(void)
{
    uint64 rsp;
    asm volatile("mov %%rsp, %0" : "=r"(rsp));
    set_tss_stack(0x10, rsp);
    flush_tss();
    sti();
    fire_userspace();
    while (1);
     hlt();

    // init_tty();
    init_threads();
    generateThread_fromRoutine(test, "kernel thread");
    kprint("OUTSIDE THREAD\n");
    while (1) hlt();
}
