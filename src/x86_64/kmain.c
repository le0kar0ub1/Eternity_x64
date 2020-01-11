#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"
#include "descriptors.h"

void init_tty(void);
void fire_userspace(void);
void userspace(void);

void yo(void)
{
    kprint("thread yooooooo\n");
    while (1);
    // exit(0);
}

void ya(void)
{
    kprint("thread yaaaaaaaa\n");
    while (1);
}

void kmain(void)
{
    // init_tty();
    // sti();
    // fire_userspace();
    // while (1);
    init_threads();
    // generateThread_fromRoutine(userspace, "userspace root");
    generateThread_fromRoutine(yo, "yoyo les amis");
    // generateThread_fromRoutine(ya, "yoyo les amis");
    sti();
    /* unreachable code bcs the userspace thread will be fired and no return are possible */
    while (0x1);
}
