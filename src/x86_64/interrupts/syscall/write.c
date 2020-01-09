#include "eternity.h"

int64 syscall_write(uint64 sz, void *ptr, uint64 fd)
{
    /* file descriptor are not handled */
    if (fd != 0x1)
        return (-0x1);
    char *s = (char *)ptr;
    for (; sz; sz--, s++)
        kprint("%c", *s);
    return (0);
}