bits 64

global fire_userspace

extern gdtUserCode
extern gdtUserData

[section .text]
fire_userspace:
    mov ax, 0x23
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push 0x23 ; segment user data DPL3 (0x20 + 0x3)
    push rsp
    pushfq
    
    push 0x1B ; segment user code DPL3 (0x18 + 0X3)
    lea rax, [userspaceJmp]
    push rax
    iretq

userspaceJmp:
    jmp userspaceJmp
    add rsp, 8
    ret

