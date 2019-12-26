#include "pmm.h"
#include "eternity.h"

/* PMM IS MANAGED BY A BIG BITMAP */

extern uint64 __KERNEL_PHYS_END;

/* start a the end of kernel phys */
uint64 pmmStart;
uint64 pmmEnd;
/* a bitmap who manage pmm static memory */
uint8 *bitmapManager = (uint8 *)(&__KERNEL_PHYS_END);
uint64 blockNbr;

/* pmm initialization */
void init_pmm(void)
{
    blockNbr = PMM_SIZE / FRAME_SIZE;
    bitmapManager = (uint8 *)ALIGN_FRAME((uint64)bitmapManager);
    memset(bitmapManager, 0x0, blockNbr);
    /* start pmm at next aligned address after bitmap */
    pmmStart = (uint64)ALIGN_FRAME(((uint64)(bitmapManager + blockNbr)));
    pmmEnd = (uint64)(pmmStart + PMM_SIZE);
}

physaddr frame_allocator(uint64 size)
{
    if (size < 0x1)
        return (0x0);
    uint frameRequest = ALIGN_FRAME(size);
    return (allocate_frame(frameRequest));
}

/* allocate consecutive frame & set the bit in bitmapManager */
physaddr allocate_frame(uint frameRequest)
{
    uint64 block = find_free_frame(frameRequest);
    SETBITMAP(block, frameRequest);
    return ((physaddr)(block * FRAME_SIZE) + pmmStart);
}


/* free the frame & clear the bit in bitmapManager */
void free_frame(physaddr addr)
{
    if (!IS_PAGE_ALIGNED(addr))
        return;
    uint block = addr / FRAME_SIZE;
    uint bitstate = BITSTATE(block);
    for (; bitstate; bitstate--) {
        CLEARBITMAP(block);
        block++;
    }
}

/* find consecutive free frame */
uint64 find_free_frame(uint frameNbr)
{
    uint keep = frameNbr;
    uint first;
    uint bitstate;

    for (uint64 bit = 0x0; bit < blockNbr; bit++) {
        bitstate = BITSTATE(bit);
        if (!bitstate) {
            first = bit;
            frameNbr--;
        } else {
            bitstate--;
            frameNbr = keep;
        }
        if (!frameNbr)
            return (first);
    }
    PANIC("No PMM available, kernel crashed...");
    return (0x0);
}

/* useful toolchain */
uint64 free_frame_nbr(void)
{
    uint64 res = 0x0;

    for (uint64 i = 0x0; i < blockNbr; i++)
        if (!BITSTATE(i))
            res++;
    return (res);
}
