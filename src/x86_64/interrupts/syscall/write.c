#include "eternity.h"

int64 syscall_write(char c)
{
    kprint("%c", c);
    return (0);
}