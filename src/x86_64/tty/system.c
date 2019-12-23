#include "eternity.h"
#include "rtc.h"

extern char const *ttyCmdDef[];

void uname(void)
{
    kprint("Eternity_x64 release 1.0\n");
}

void help(void)
{
    kprint("Available commands:\n");
    for (uint i = 0x0; ttyCmdDef[i]; i++)
        kprint("    %s\n", ttyCmdDef[i]);
}

void rtctime(void)
{
    char *time = get_cmos_rtc_time();
    kprint("%s\n", time);
    kfree(time);
}
