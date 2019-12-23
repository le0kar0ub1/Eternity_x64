#ifndef RTC_H
#define RTC_H

/* RTC IN (a part of) CMOS REGISTER */

#include "eternity.h"

struct rtcTime {
    uint8 century;
    uint8 year;
    uint8 month;
    uint8 day;
    uint8 hour;
    uint8 minute;
    uint8 second;
};

int is_updating_rtc(void);
uint8 get_rtc_register(uint8 regs);
void set_rtc_register(uint16 regs, uint8 val);
void write_rtc(struct rtcTime *wr);
void read_rtc(void);
void init_rtc(void);
char *get_cmos_rtc_time(void);

#endif
