#include "eternity.h"
#include "pic.h"
#include "interrupt.h"
#include "timer.h"

/* Internal timer counters */
uint64 ticks    = 0x0;
uint8  subTicks = 0x0;

void timer_handler(struct frame *frame)
{
    if (++subTicks == SUBTICKS_PER_TICK) {
        ticks++;
        subTicks = 0x0;
        kprint("%d ", ticks);
    }
    frame->rax = 0x0;
    pic_eoi(IRQ0);
}

void reset_timer(void)
{
    ticks = 0x0;
    subTicks = 0x0;
}

uint64 getTime(void)
{
    return (ticks);
}

void relative_time(uint64 seconds, uint64 subseconds, uint64 *out_seconds, uint64 *out_subseconds)
{
    if (subseconds + subTicks > SUBTICKS_PER_TICK) {
        *out_seconds    = ticks + seconds + 0x1;
        *out_subseconds = (subseconds + subTicks) - SUBTICKS_PER_TICK;
    } else {
        *out_seconds    = ticks + seconds;
        *out_subseconds = subTicks + subseconds;
    }
}

void timer_phase(int freq)
{
    int div = PIT_SCALE / freq;
    outb(PIT_CONTROL, PIT_SET);
    outb(PIT_A, div & PIT_MASK);
    outb(PIT_A, (div >> 0x8) & PIT_MASK);
}

void init_timer(void)
{
    timer_phase(0x64); /* 100Hz */
    register_int_handler(INT_IRQ0, timer_handler);
    pic_unmask(IRQ0);
}
