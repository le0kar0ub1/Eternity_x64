#include "eternity.h"
#include "interrupt.h"
#include "syscall.h"


void syscall_handler(struct frame *frame)
{
    __asm__("push %rdx");
    __asm__("push %rcx");
    kprint("IN SYSCALL HANDLER int: %d\n", frame->rax);
    hlt();
    switch (frame->rax) {
        case SYSCALL_READ:
            kprint("SYSCALL_READ\n");
        case SYSCALL_WRITE:
            kprint("SYSCALL_WRITE\n");
        default:
            frame->rax = 0x0;
    }
    __asm__("pop %rcx");
    __asm__("pop %rdx");
    __asm__("sysexit");
}
