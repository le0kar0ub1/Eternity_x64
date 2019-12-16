#include "eternity.h"

void *memset(void *ptr, uint8 value, size_t size)
{
    uint8 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}

void *memsetw(void *ptr, uint16 value, size_t size)
{
    uint16 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}

void *memsetd(void *ptr, uint32 value, size_t size)
{
    uint32 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}

void *memsetq(void *ptr, uint64 value, size_t size)
{
    uint64 *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}
