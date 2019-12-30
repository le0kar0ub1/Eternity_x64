#ifndef _TIMER_H_
#define _TIMER_H_

#include "eternity.h"

#define PIT_A 0x40
#define PIT_B 0x41
#define PIT_C 0x42
#define PIT_CONTROL 0x43

#define PIT_MASK 0xFF
#define PIT_SCALE 1193180
#define PIT_SET 0x36

#define TIMER_FREQUENCY 0x64

struct functionWakeUp {
    struct functionWakeUp *next;
    void (*fnct)();
    uint32 cs;
    uint32 current;
};
void register_functionWakeup(void *fnct, uint32 cs);
void unregister_functionWakeup(void *fnct);

void init_timer(void);
void sleep(uint8 sec);
void timer_phase(int freq);
void timer_handler(struct frame *frame);
void relative_time(uint64 seconds, uint64 subseconds, uint64 *out_seconds, uint64 *out_subseconds);
void reset_timer(void);
uint64 getTime(void);


#endif
