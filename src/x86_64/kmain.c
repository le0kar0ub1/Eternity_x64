#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"
#include "descriptors.h"

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
    init_tty();
    fire_userspace();
    // init_threads();
    // generateThread_fromRoutine(test, "Userspace thread");
    kprint("OUTSIDE THREAD\n");
    while (1) hlt();
}
