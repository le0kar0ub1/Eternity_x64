#include "eternity.h"

void *memset(void *ptr, int value, size_t size)
{
    uchar *tmp = ptr;

    if (tmp == NULL)
        return (NULL);
    for (size_t i = 0x0; i < size ; i++)
        tmp[i] = value;
    return (ptr);
}
