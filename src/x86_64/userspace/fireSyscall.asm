bits 64

global fireSyscall

[section .text]
fireSyscall:
    mov rax, rdi
    int 0x80
    ret