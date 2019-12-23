#include "eternity.h"

int strcmp(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (-0x1);
    for (; *s1 && *s2 && *s1 == *s2; s1++, s2++);
    if (*s1 == 0x0 && *s2 == 0x0)
        return (0x1);
    return (0x0);
}

int strncmp(char const *s1, char const *s2, size_t size)
{
    if (s1 == NULL || s2 == NULL)
        return (-0x1);
    for (; *s1 && *s2 && *s1 == *s2 && size != 0x0; s1++, s2++, size--);
    if ((*s1 == 0x0 && *s2 == 0x0) || size == 0x0)
        return (0x1);
    return (0x0);
}

int strlen(char const *s)
{
    int i = 0x0;

    if (s == NULL)
        return (0x0);
    for (; s[i]; i++);
    return (i);
}

void strcat(char *s1, char const *s2)
{
    if (!s1 || !s2)
        return;
    uint i = strlen(s1);
    uint j = i;
    for (; s2[i - j]; i++)
        s1[i] = s2[i - j];
    s1[i] = 0x0;
    // char *new = kalloc(strlen(s1) + strlen(s2) + 0x1);
    // uint i = 0x0;
    // for (; s1[i]; i++)
    //     new[i] = s1[i];
    // i++;
    // for (uint j = 0x0; s2[j]; j++, i++)
    //     new[i] = s2[j];
    // new[i] = 0x0;
}

void itoa(char *buf, uint64 n, int base)
{
    uint64 tmp = n;
    int i = 0x0, j = 0x0;

    while (n) {
        tmp = n % base;
        buf[i] = (tmp < 0xA) ? (tmp + '0') : (tmp + 'a' - 0xA);
        n /= base;
        i += 0x1;
    }
    buf[i] = 0x0;
    i--;
    for (; j < i; j++, i--) {
        tmp = buf[j];
        buf[j] = buf[i];
        buf[i] = tmp;
    }
}

char *strcpy(char *d, char const *s)
{
    int i = 0x0;

    for (; s[i]; i++)
        d[i] = s[i];
    d[i] = 0x0;
    return (d);
}
