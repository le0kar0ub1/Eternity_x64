#include "eternity.h"
#include "syscall.h"
#include "syscall_prototypes.h"

void fireSyscall(uint64 vector, ...);

void proc(void)
{
    char s[30] = "inside second process\n";
    write(strlen(s), (char *)&s, 1);
    while(1);
}

void userspace(void)
{
    char s[30] = "hello from userspace\n";
    write(strlen(s), (char *)&s, 1);
    exec(proc, "procn");
    while (1);
    exit(0);
}