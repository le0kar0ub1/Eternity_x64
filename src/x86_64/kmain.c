#include "eternity.h"
#include "virtualSegment.h"

void init_tty(void);
void fire_userpace(void);

void kmain(void)
{
    hlt();
    sti();
    init_tty();
    // fire_userspace();
    while (1) hlt();
}
