bits 64

global fire_userspace

extern gdtUserCode
extern gdtUserData

extern userspace

[section .text]
fire_userspace:
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push 0x23 ; segment user data DPL3 (0x20 + 0x3)
    push rdi
    ; push rsp
    pushfq
    pop rax
    or rax , 0x3200 ; DPL 3
    push rax

    push 0x1B ; segment user code DPL3 (0x18 + 0X3)
    lea rax, [userspace]
    push rax
    iretq ; use iret to jump into usermode