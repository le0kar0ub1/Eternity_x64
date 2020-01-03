#include "eternity.h"

void fireSyscall(uint64 vector);

void userspace(void)
{
    fireSyscall(0x0);
    while (1);
}