#include "eternity.h"
#include "virtualSegment.h"
#include "threads.h"
#include "descriptors.h"

void init_tty(void);
void fire_userspace(void);
void userspace(void);

void kmain(void)
{
    // init_tty();
    // fire_userspace();
    init_threads();
    generateThread_fromRoutine(userspace, "userspace root");
    sti();
    /* unreachable code bcs the userspace thread will be fired and no return are possible */
    while (0x1);
}
