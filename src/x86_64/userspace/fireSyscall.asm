%include "syscall.inc"

bits 64

global fireSyscall
global write
global exec
global exit

[section .text]
fsyscall:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, r10
    mov r10, r8
    syscall
    ret

write:
    mov rax, SYSCALL_WRITE
    syscall
    ret

exec:
    mov rax, SYSCALL_EXEC
    syscall
    ret

exit:
    mov rax, SYSCALL_EXIT
    syscall
    ret