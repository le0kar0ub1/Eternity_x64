#include "eternity.h"
#include "syscall.h"
#include "syscall_prototypes.h"

extern uint64 *syscall_table;

void syscall_register_init(void)
{
    register_syscall_handler(SYSCALL_WRITE, syscall_write);
    register_syscall_handler(SYSCALL_EXIT, syscall_exit);
    register_syscall_handler(SYSCALL_EXEC, syscall_exec);
}