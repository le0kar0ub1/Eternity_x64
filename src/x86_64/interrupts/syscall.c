#include "eternity.h"
#include "interrupt.h"
#include "syscall.h"

void syscall_handler(struct frame *frame)
{
    switch (frame->rax) {
        case SYSCALL_READ:
            kprint("SYSCALL_READ\n");
        case SYSCALL_WRITE:
            kprint("SYSCALL_WRITE\n");
        default:
            frame->rax = 0x0;
    }
}
