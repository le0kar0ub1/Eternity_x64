bits 64

global fireSyscall
global write

[section .text]
fireSyscall:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, r10
    mov r10, r8
    syscall
    ret

write:
    mov rax, 0x1
    syscall
    ret