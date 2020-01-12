#ifndef _SOUND_H_
#define _SOUND_H_

#include "typedef.h"

/* table freq musical by octave */
enum DO /* or SI# */
{
    DOoct0 = 16,
    DOoct1 = 33,
    DOoct2 = 64,
    DOoct3 = 131,
    DOoct4 = 262,
    DOoct5 = 523,
    DOoct6 = 1046,
    DOoct7 = 2093,
    DOoct8 = 4186,
    DOoct9 = 8372,
    DOoct10 = 16744,
};

enum RE
{
    REoct0 = 18,
    REoct1 = 37,
    REoct2 = 73,
    REoct3 = 147,
    REoct4 = 294,
    REoct5 = 587,
    REoct6 = 1175,
    REoct7 = 2349,
    REoct8 = 4699,
    REoct9 = 9397,
    REoct10 = 18795,
};

enum MI /* or FAb */
{
    MIoct0 = 21,
    MIoct1 = 41,
    MIoct2 = 82,
    MIoct3 = 165,
    MIoct4 = 330,
    MIoct5 = 659,
    MIoct6 = 1319,
    MIoct7 = 2637,
    MIoct8 = 5274,
    MIoct9 = 10548,
    MIoct10 = 21096,
};

enum FA /* MI# */
{
    FAoct0 = 22,
    FAoct1 = 44,
    FAoct2 = 87,
    FAoct3 = 175,
    FAoct4 = 349,
    FAoct5 = 698,
    FAoct6 = 1397,
    FAoct7 = 2794,
    FAoct8 = 5588,
    FAoct9 = 11175,
    FAoct10 = 22351,
};

enum SOL
{
    SOLoct0 = 24,
    SOLoct1 = 49,
    SOLoct2 = 98,
    SOLoct3 = 196,
    SOLoct4 = 392,
    SOLoct5 = 784,
    SOLoct6 = 1568,
    SOLoct7 = 3136,
    SOLoct8 = 6272,
    SOLoct9 = 12544,
    SOLoct10 = 25088,
};

enum LA
{
    LAoct0 = 27,
    LAoct1 = 55,
    LAoct2 = 110,
    LAoct3 = 220,
    LAoct4 = 440,
    LAoct5 = 880,
    LAoct6 = 1760,
    LAoct7 = 3520,
    LAoct8 = 7040,
    LAoct9 = 14080,
    LAoct10 = 28160,
};

enum SI /* DOb */
{
    SIoct0 = 31,
    SIoct1 = 62,
    SIoct2 = 123,
    SIoct3 = 247,
    SIoct4 = 494,
    SIoct5 = 988,
    SIoct6 = 1976,
    SIoct7 = 3951,
    SIoct8 = 7902,
    SIoct9 = 15804,
    SIoct10 = 31609,
};

void play_sound(uint32 freq);
void sound_off(void);
void beep(void);

#endif
