#include "eternity.h"

int64 syscall_write(uint64 sz, char *s, uint64 fd)
{
    if (fd != 0x1)
        return (-0x1);
    for (; sz; sz--, s++)
        kprint("%c", *s);
    return (0);
}