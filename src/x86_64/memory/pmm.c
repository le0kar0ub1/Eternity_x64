#include "pmm.h"
#include "eternity.h"

extern uint64 __KERNEL_PHYS_END;

/* start a the end of kernel phys */
uint8 *pmmStart;
/* a bitmap who manage pmm static memory */
uint8 *bitmapManager = (uint8 *)(&__KERNEL_PHYS_END);

void init_pmm(uint64 size)
{
    uint blockNbr = size / BLOCK_SIZE;
    memset(bitmapManager, 0x0, blockNbr);
    /* start pmm at next aligned address after bitmap */
    pmmStart = (uint8 *)ALIGN_BLOCK(((uint64)(bitmapManager + blockNbr)));
}
