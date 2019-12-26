bits 64

global fire_userspace

extern gdtUserCode
extern gdtUserData

[section .text]
fire_userspace:
    mov rcx, rdi ; stack pointer
    mov rdx, rsi ; function to call

    mov ax, gdtUserData
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rax, gdtUserData
    ; or rax, 0b11
    push rax ; push user data selector

    mov rcx, userspaceStack
    push rcx

    pushf
    ; push QWORD 0x3202

    ; mov rax, rsp
    ; push rax ; push current instruction pointer

    mov rax, gdtUserCode
    ; or rax, 0b11
    push rax ; push user code selector

    mov rdx, _test_user_function
    push rdx ; next instruction

    iretq ; magic happen


_test_user_function:
    jmp _test_user_function


[section .bss]
align 0x400
userspaceStack:
    RESB (0x1000 * 0x4)
