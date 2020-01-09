#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"
#include "descriptors.h"

void init_tty(void);
void fire_userspace(void);

void userspaceRoot(void)
{
    while (1)
        kprint("first\n");
}

void scnd(void)
{
    while (1) 
        kprint("second\n");
}

void kmain(void)
{
    // init_tty();
    // sti();
    // fire_userspace();
    // cli();
    init_threads();
    // sti();
    generateThread_fromRoutine(userspaceRoot, "userspace root");
    generateThread_fromRoutine(scnd, "test second");
    threadListDump();
    while(1);
    while (1)
       kprint("OUTSIDE\n");
}
