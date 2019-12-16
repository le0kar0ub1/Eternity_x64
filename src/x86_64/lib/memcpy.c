#include "eternity.h"

void *memcpy(void *dest, void *src, size_t size)
{
    uint8 *d = dest;
    uint8 *s = src;

    if (d == NULL || s == NULL)
        return (NULL);
    for (size_t i = 0x0; i != size ; i++)
        d[i] = s[i];
    return (dest);
}

void *memcpyw(void *dest, void *src, size_t size)
{
    uint16 *d = dest;
    uint16 *s = src;

    if (d == NULL || s == NULL)
        return (NULL);
    for (size_t i = 0x0; i != size ; i++)
        d[i] = s[i];
    return (dest);
}

void *memcpyd(void *dest, void *src, size_t size)
{
    uint32 *d = dest;
    uint32 *s = src;

    if (d == NULL || s == NULL)
        return (NULL);
    for (size_t i = 0x0; i != size ; i++)
        d[i] = s[i];
    return (dest);
}

void *memcpyq(void *dest, void *src, size_t size)
{
    uint64 *d = dest;
    uint64 *s = src;

    if (d == NULL || s == NULL)
        return (NULL);
    for (size_t i = 0x0; i != size ; i++)
        d[i] = s[i];
    return (dest);
}
