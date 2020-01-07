%include "descriptors.inc"
%include "syscall.inc"

bits 64

global syscall_handler

extern syscall_table
extern PANIC

[section .text]
; r11 get falgs
; rcx get rip
syscall_handler:
    ; System don't manage the stack switch so
    ; we must load a kernel stack and then reload the user stack after
    mov r10, rsp ; user stack
    mov rsp, kernel_syscall_stack_address

    push QWORD (USER_DATA_SELECTOR | 0x3) ; dpl3
    push QWORD r10 ; user stack
    push QWORD r11 ; also flags
    push QWORD (USER_CODE_SELECTOR | 0x3) ; dpl3
    push QWORD rcx ; also rip

    ; kernel syscall stack can handle interrupts
    sti

    ; for it... we don't need to save register when syscall occured normally
    ; but i find that is most proper and easy for developpers
    push rdi
    push rsi
    push rbx
    push rdx
    push r10
    push r12
    push r13
    push r14
    push r15

    cmp rax, x86_MAX_SYSCALL
    jae syscallCrashed

    mov rax, QWORD [syscall_table + (rax * 0x8)] ; pointer on handler
    cmp rax, 0x0
    je syscallCrashed

    call rax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r10
    pop rdx
    pop rbx
    pop rsi
    pop rdi

    ; clear r11 & rcx
    xor r11, r11
    xor rcx, rcx
    ; rax already contain the return value
    iretq

syscallCrashed:
    mov rdi, syscallCrashedError
    call PANIC

[section .rodata]
    syscallCrashedError db "Syscall request is out of range or not already handle", 0xA, 0x0

[section .bss]
kernel_syscall_stack: RESB 0x1000

[section .data]
kernel_syscall_stack_address DQ kernel_syscall_stack