%include "descriptors.inc"
%include "rflags.inc"

bits 64

global fire_userspace

extern gdtUserCode
extern gdtUserData

extern userspace

[section .text]
fire_userspace:
    mov ax, (USER_DATA_SELECTOR | 0x3)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push (USER_DATA_SELECTOR | 0x3) ; segment user data DPL3
    push rdi
    ; push rsp
    pushfq
    pop rax
    or rax, IOPLBL | IOPLBH ; DPL 3
    ; or rax, IF
    push rax

    push (USER_CODE_SELECTOR | 0x3) ; segment user code DPL3
    lea rax, [userspace]
    push rax
    iretq ; use iret to jump into usermode