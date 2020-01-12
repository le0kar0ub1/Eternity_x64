#include "eternity.h"
#include "pic.h"
#include "interrupt.h"
#include "timer.h"
#include "cpuContext.h"

/* list of function call all x sec */
struct functionWakeUp *functionWakeUp;

/* Internal timer counters */
uint64 ticks    = 0x0;
uint8  subTicks = 0x0;

void timer_handler(struct frame *frame)
{
    if (++subTicks == TIMER_FREQUENCY) {
        ticks++;
        subTicks = 0x0;
    }
    /* current cpu context update each 0.1 sec */
    struct cpuContext *context = getCpuContext();
    memcpy(context, frame, sizeof(struct frame) & sizeof(struct cpuContext));
    struct functionWakeUp *list = functionWakeUp;
    for (; list; list = list->next) {
        if (++list->current == list->cs) {
            /* set to 0 now bcs when this trigger a context switch, there is no come back here... */
            list->current = 0x0;
            /* then call the function */
            list->fnct();
        }
    }
    pic_eoi(IRQ0);
}

/* Really bad implementation */
void sleep(uint8 sec)
{
    uint64 needTick = ticks + sec;
    uint8 needSub = subTicks;
    while (ticks < needTick);
    while (needSub != subTicks);
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
    if (subseconds + subTicks > TIMER_FREQUENCY) {
        *out_seconds    = ticks + seconds + 0x1;
        *out_subseconds = (subseconds + subTicks) - TIMER_FREQUENCY;
    } else {
        *out_seconds    = ticks + seconds;
        *out_subseconds = subTicks + subseconds;
    }
}

void register_functionWakeup(void *fnct, uint32 cs)
{
    struct functionWakeUp *list = functionWakeUp;

    for (; list && list->next && list->fnct; list = list->next);
    if (!(list->fnct)) {
        list->fnct = fnct;
        list->cs = cs;
    } else {
        list->next = kalloc(sizeof(struct functionWakeUp));
        list->next->next = NULL;
        list->next->cs = cs;
        list->next->current = 0x0;
        list->next->fnct = fnct;
    }
}

void unregister_functionWakeup(void *fnct)
{
    struct functionWakeUp *list = functionWakeUp;

    for (; list && list->fnct; list = list->next)
        if (list->fnct == fnct) {
            list->fnct = NULL;
            break;
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
    timer_phase(TIMER_FREQUENCY); /* 100Hz */
    register_int_handler(INT_IRQ0, timer_handler);
    functionWakeUp = kalloc(sizeof(struct functionWakeUp));
    memset(functionWakeUp, 0x0, sizeof(struct functionWakeUp));
    pic_unmask(IRQ0);
}
