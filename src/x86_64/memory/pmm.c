#include "pmm.h"
#include "eternity.h"

extern uint64 __KERNEL_PHYS_END;

/* start a the end of kernel phys */
uint64 pmmStart;
/* a bitmap who manage pmm static memory */
uint8 *bitmapManager = (uint8 *)(&__KERNEL_PHYS_END);
uint64 blockNbr;

/* pmm initialization */
void init_pmm(uint64 size)
{
    size = PMM_SIZE;
    blockNbr = size / BLOCK_SIZE;
    memset(bitmapManager, 0x0, blockNbr);
    /* start pmm at next aligned address after bitmap */
    pmmStart = (uint64 )ALIGN_BLOCK(((uint64)(bitmapManager + blockNbr)));
}

void *frame_allocator(uint64 size)
{
    if (size < 0x1)
        return (0x0);
    uint frameRequest = ALIGN_BLOCK(size);

    if (frameRequest == 0x1)
        return ((void *)allocate_frame());
    else
        return ((void *)allocate_consecutive_frame(frameRequest));
}

/* allocate consecutive frame & set the bit in bitmapManager */
uint64 allocate_consecutive_frame(uint frameRequest)
{
    uint64 block = find_consecutive_free_frame(frameRequest);
    for (; frameRequest > 0x0; frameRequest--)
        SETBITMAP(block + frameRequest);
    block = (block * BLOCK_SIZE) + pmmStart;
    return (block);
}

/* allocate a frame & set the bit in bitmapManager */
uint64 allocate_frame(void)
{
    uint64 block = find_free_frame();
    SETBITMAP(block);
    block = (block * BLOCK_SIZE) + pmmStart;
    return (block);
}

/* free the frame & clear the bit in bitmapManager */
void free_frame(uint64 block)
{
    CLEARBITMAP(block);
}

/* find a free frame */
uint64 find_free_frame(void)
{
    for (uint64 i = 0x0; i < blockNbr; i++)
        if (!BITSTATE(i))
            return (i);
    PANIC("No pmm available, kernel crash...");
    return (0x0);
}

/* find consecutive free frame */
uint64 find_consecutive_free_frame(uint frameNbr)
{
    uint keep = frameNbr;
    uint first;

    for (uint64 bit = 0x0; bit < blockNbr; bit++) {
        if (!BITSTATE(bit)) {
            first = bit;
            frameNbr -= 0x1;
        } else
            frameNbr = keep;
        if (!frameNbr)
            return (first);
    }
    PANIC("No pmm available, kernel crash...");
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
