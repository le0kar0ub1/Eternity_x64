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

char *strcpy(char *d, char const *s)
{
    int i = 0x0;

    for (; s[i]; i++)
        d[i] = s[i];
    d[i] = 0x0;
    return (d);
}
