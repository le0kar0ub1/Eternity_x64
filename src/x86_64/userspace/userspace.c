#include "eternity.h"
#include "syscall.h"

void fireSyscall(uint64 vector);

void userspace(void)
{
    fireSyscall(SYSCALL_WRITE);
    while (1);
}