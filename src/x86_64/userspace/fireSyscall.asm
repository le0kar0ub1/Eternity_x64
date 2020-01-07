bits 64

global fireSyscall

[section .text]
fireSyscall:
    mov rax, 0x1
    syscall
    ret