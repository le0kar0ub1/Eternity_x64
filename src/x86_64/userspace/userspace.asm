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

    push 0x23
    push rsp
    pushfq
    
    push 0x1B
    lea rax, [userspaceJmp]
    push rax
    iret

userspaceJmp:
    jmp userspaceJmp
    add rsp, 8
    ret

