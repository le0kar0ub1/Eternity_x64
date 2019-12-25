global fire_userspace

%define GDT_ENTRY_SIZE 0x8

%define GDT_NULL_ENTRY        0x0
%define GDT_KERNEL_CODE_ENTRY 0x1
%define GDT_KERNEL_DATA_ENTRY 0x2
%define GDT_USER_CODE_ENTRY   0x3
%define GDT_USER_DATA_ENTRY   0x4
%define GDT_TSS_ENTRY         0x5

[section .text]
fire_userspace:
    mov rcx, rdi ; stack pointer
    mov rdx, rsi ; function to call

    mov ax, (GDT_USER_DATA_ENTRY * GDT_ENTRY_SIZE)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov rax, GDT_USER_DATA_ENTRY
    mov rdi, GDT_ENTRY_SIZE
    mul rdi
    or rax, 0b11
    push rax ; push user data selector

    push rcx

    pushf
    ; push QWORD 0x3202

    ; mov rax, rsp
    ; push rax ; push current instruction pointer

    mov rax, GDT_USER_CODE_ENTRY
    mov rdi, GDT_ENTRY_SIZE
    mul rdi
    or rax, 0b11
    push rax ; push user code selector

    mov rdx, _test_user_function
    push rdx ; next instruction

    iretq


_test_user_function:
    hlt
    jmp _test_user_function
