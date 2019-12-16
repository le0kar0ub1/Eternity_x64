#include "pmm.h"
#include "eternity.h"

extern uint64 __KERNEL_PHYS_END;

/* start a the end of kernel phys */
uint8 *start = (uint8 *)(&__KERNEL_PHYS_END);
/* a bitmap who manage pmm static memory */
uint8 *bitmapManager = (uint8 *)(&__KERNEL_PHYS_END);

void init_pmm(uint64 size)
{

}
