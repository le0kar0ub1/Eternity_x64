#include "eternity.h"

void *memsetb(void *ptr, int value, size_t size)
{
    uint8 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}

void *memsetw(void *ptr, int value, size_t size)
{
    uint16 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}

void *memsetd(void *ptr, int value, size_t size)
{
    uint32 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}

void *memsetq(void *ptr, int value, size_t size)
{
    uint64 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}
