#include "pmm.h"
#include "eternity.h"

extern uint64 __KERNEL_VIRT_END;

/* a bitmap who manage pmm static memory */
uint8 *bitmap = (uint8 *)(&__KERNEL_VIRT_END);

/* pmm initialization */
void init_pmm(void)
{
    bitmap = (uint8 *)ALIGN_FRAME((uint64)bitmap);
    memset(bitmap, 0x0, BITMAP_SIZE);
}

void mark_pmm_as_allocated(physaddr_t start, physaddr_t end)
{
    if (!IS_PAGE_ALIGNED(start))
        start = ROUND_DOWN(start);
    if (!IS_PAGE_ALIGNED(end))
        end = ALIGN_FRAME(end);
    if (end > BITMAP_SIZE * FRAME_SIZE)
        PANIC("PMM request is out ouf memory\n");
    for (uint8 tmp = (uint8)start; tmp < end / FRAME_SIZE; tmp++)
        if (BITSTATE(tmp))
            PANIC("PMM request is already mapped\n");
    uint8 request = end / FRAME_SIZE - start / FRAME_SIZE;
    for (uint8 tmp = (uint8)(start / FRAME_SIZE); tmp < end / FRAME_SIZE; tmp++) {
        SETBITMAP(tmp, request);
        request = 0x1;
    }
}

physaddr_t frame_allocator(uint64 size)
{
    if (size < 0x1)
        return (0x0);
    uint frameRequest = ALIGN_FRAME(size) / FRAME_SIZE;
    return (allocate_frame(frameRequest));
}

/* allocate consecutive frame & set the bit in bitmap */
physaddr_t allocate_frame(uint frameRequest)
{
    uint64 block = find_free_frame(frameRequest);
    SETBITMAP(block, frameRequest);
    return ((physaddr_t)(block * FRAME_SIZE));
}


/* free the frame & clear the bit in bitmap */
void free_frame(physaddr_t addr)
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

    for (uint64 bit = 0x0; bit < BITMAP_SIZE; bit++) {
        bitstate = BITSTATE(bit);
        if (!bitstate) {
            if (keep == frameNbr)
                first = bit;
            frameNbr--;
        } else {
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

    for (uint64 i = 0x0; i < BITMAP_SIZE; i++)
        if (!BITSTATE(i))
            res++;
    return (res);
}
