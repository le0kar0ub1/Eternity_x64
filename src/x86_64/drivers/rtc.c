#include "rtc.h"
#include "ports.h"

struct rtcTime rtcTime;

int is_updating_rtc(void)
{
    outb(PORT_CMOS, 0x0A);
    uint32 status = inb(PORT_CMOS_DATA);
    return (status & 0x80);
}

uint8 get_rtc_register(uint8 regs)
{
    outb(PORT_CMOS, regs);
    return (inb(PORT_CMOS_DATA));
}

void set_rtc_register(uint16 regs, uint8 val)
{
    outb(PORT_CMOS, regs);
    outb(PORT_CMOS_DATA, val);
}

void write_rtc(struct rtcTime *wr)
{
    while(is_updating_rtc());

    set_rtc_register(0x00, wr->second);
    set_rtc_register(0x02, wr->minute);
    set_rtc_register(0x04, wr->hour);
    set_rtc_register(0x07, wr->day);
    set_rtc_register(0x08, wr->month);
    set_rtc_register(0x09, wr->year);
}

void read_rtc(void)
{
    while(is_updating_rtc());

    rtcTime.second = get_rtc_register(0x00);
    rtcTime.minute = get_rtc_register(0x02);
    rtcTime.hour = get_rtc_register(0x04);
    rtcTime.day = get_rtc_register(0x07);
    rtcTime.month = get_rtc_register(0x08);
    rtcTime.year = get_rtc_register(0x09);

    uint8 regsSpec = get_rtc_register(0x0B);

    // Convert BCD to binary values if necessary
    if (!(regsSpec & 0x04)) {
        rtcTime.second = (rtcTime.second & 0x0F) + ((rtcTime.second / 0x10) * 0xA);
        rtcTime.minute = (rtcTime.minute & 0x0F) + ((rtcTime.minute / 0x10) * 0xA);
        rtcTime.hour = ( (rtcTime.hour & 0x0F) + (((rtcTime.hour & 0x70) / 0x10) * 0xA) ) | (rtcTime.hour & 0x80);
        rtcTime.day = (rtcTime.day & 0x0F) + ((rtcTime.day / 0x10) * 0xA);
        rtcTime.month = (rtcTime.month & 0x0F) + ((rtcTime.month / 0x10) * 0xA);
        rtcTime.year = (rtcTime.year & 0x0F) + ((rtcTime.year / 0x10) * 0xA);
    }
}

char *get_cmos_rtc_time(void)
{
    struct rtcTime *rtc = &rtcTime;
    char *ret = kalloc(0x10);
    char month[4];
    char day[4];
    char hour[3];
    char min[3];

    memset(&month, 0x0, 4);
    memset(&day, 0x0, 4);
    memset(&hour, 0x0, 3);
    memset(&min, 0x0, 3);

    if (rtc->day) {
        if (rtc->day < 10)
            strcat(ret, "0");
        itoa(day, rtc->day, 10);
        for (uint i = 0x0; day[i]; i++)
            ret[i] = day[i];
        ret[strlen(day)] = 0x0;
    } else
        strcat(ret, "00");

    strcat(ret, "/");

    if (rtc->month) {
        if (rtc->month < 10)
            strcat(ret, "0");
        itoa(month, rtc->month, 10);
        strcat(ret, month);
    } else
        strcat(ret, "00");

    strcat(ret, " ");

    if (rtc->hour) {
        if (rtc->hour < 10)
            strcat(ret, "0");
        itoa(hour, rtc->hour, 10);
        strcat(ret, hour);
    } else
        strcat(ret, "00");

    strcat(ret, ":");

    if (rtc->minute) {
        if (rtc->minute < 10)
            strcat(ret, "0");
        itoa(min, rtc->minute, 10);
        strcat(ret, min);
    } else
        strcat(ret, "00");
    return (ret);
}

void init_rtc(void)
{
    read_rtc();
}
