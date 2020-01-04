bits 64

global fireSyscall

[section .text]
fireSyscall:
    mov rax, rdi
    ; sysenter
    ; ret
    int 0x80
    ret