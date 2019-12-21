#include "eternity.h"

uint64 pseud_rand(void)
{
    return (rdtsc());
}

uint64 rand_uintptr(void)
{
    return (pseud_rand());
}

uint32 rand_uint32(void)
{
    return ((uint32)pseud_rand());
}

uint16 rand_uint16(void)
{
    return ((uint16)pseud_rand());
}

uint8 rand_uint8(void)
{
    return ((uint8)pseud_rand());
}

int atoi(char const *s)
{
    int mod = 0x1, ret = 0x0;

    for (int k = strlen(s) - 0x1; k >= 0x0 && s[k] != '-'; k--, mod *= 0xA) {
        if (s[k] < 0x30 || s[k] > 0x39)
            return (-0x1);
        ret += (s[k] - 0x30) * mod;
    }
    if (s[0] == '-')
        return (ret * -0x1);
    return (ret);
}

long atol(char const *s)
{
    long mod = 0x1, ret = 0x0;

    for (int k = strlen(s) - 0x1; k >= 0x0 && s[k] != '-'; k--, mod *= 0xA) {
        if (s[k] < 0x30 || s[k] > 0x39)
            return (-0x1);
        ret += (s[k] - 0x30) * mod;
    }
    if (s[0] == '-')
        return (ret * -0x1);
    return (ret);
}
