#ifndef CMP_H_
#define CMP_H_

#include <stdbool.h>

static inline bool is_num(char c)
{
    if (c <= 0x39 && c >= 0x30)
        return (true);
    return (false);
}

static inline bool sis_num(char *s)
{
    for (; *s && is_num(*s); s++);
    if (*s == 0x0)
        return (true);
    return (false);
}

static inline bool is_alpha(char c)
{
    if ((c <= 0x7A && c >= 0x61) || c == 0x5f || is_num(c))
        return (true);
    return (false);
}

static inline bool sis_alpha(char *s)
{
    for (; *s && is_alpha(*s); s++);
    if (*s == 0x0)
        return (true);
    return (false);
}

static inline bool cmp(int x, int y)
{
    if (x != y)
        return (false);
    return (true);
}

static inline int absl(int x)
{
    return (x *= (x < 0x0) ? -0x1 : 0x1);
}

static inline bool endl(int x)
{
    if (x != 0xA && x != 0x0)
        return (false);
    return (true);
}

# define FALSE false
# define TRUE  true

#endif
