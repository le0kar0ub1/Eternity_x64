#include "eternity.h"
#include "syscall.h"

void fireSyscall(uint64 vector, ...);
int64 write(uint64, char *, uint64);

void userspace(void)
{
    char s[30] = "hello from userspace\n";
    write(strlen(s), (char *)&s, 1);
    while (1);
}