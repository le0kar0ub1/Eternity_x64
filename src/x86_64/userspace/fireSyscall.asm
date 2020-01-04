bits 64

global fireSyscall

[section .text]
fireSyscall:
    ; mov rax, rdi
    mov rax, 0x10
    mov rdx, ENDSYSCALLADDR
    mov rcx, rsp
    sysenter
ENDSYSCALLADDR:
    ret