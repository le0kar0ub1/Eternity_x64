#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"
#include "descriptors.h"

void init_tty(void);
void fire_userspace(void);
void userspace(void);

void yo(void)
{
    while (1);
    kprint("thread yooooooo\n");
    // exit(0);
}

void kmain(void)
{
    // init_tty();
    // fire_userspace();
    sti();
    while (1);
    init_threads();
    // generateThread_fromRoutine(userspace, "userspace root");
    generateThread_fromRoutine(yo, "root thread");
    sti();
    /* unreachable code bcs the root userspace thread will be fired and no return are possible */
    while (0x1);
}
