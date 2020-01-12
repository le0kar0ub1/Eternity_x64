#include "eternity.h"

bool memcmp(void *x, void *y, size_t size)
{
    for (size_t inc = 0x0; inc < size; inc++)
        if (((uint8 *)x)[inc] != ((uint8 *)y)[inc])
            return (false);
    return (true);
}