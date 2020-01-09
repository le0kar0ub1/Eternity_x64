%include "descriptors.inc"

bits 64

extern PANIC

global kernel_contextSwitch
global user_contextSwitch

[section .text]
kernel_contextSwitch:
    cmp rdi, 0x0
    je contextSwitchCrash
    mov rbx, QWORD [rdi + 0x8]
    mov rcx, QWORD [rdi + 0x10]
    mov rdx, QWORD [rdi + 0x18]
    mov rsi, QWORD [rdi + 0x20]

    mov r8,  QWORD [rdi + 0x38]
    mov r9,  QWORD [rdi + 0x40]
    mov r10, QWORD [rdi + 0x48]
    mov r11, QWORD [rdi + 0x50]
    mov r12, QWORD [rdi + 0x58]
    mov r13, QWORD [rdi + 0x60]
    mov r14, QWORD [rdi + 0x68]
    mov r15, QWORD [rdi + 0x70]

    ; SWITCH SEGMENTS
    mov ax, KERNEL_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; DATA SELECTOR
    push QWORD KERNEL_DATA_SELECTOR
    ; RSP
    mov rax, QWORD [rdi + 0x30]
    push rax
    ; rflags
    mov rax, QWORD [rdi + 0xB0]
    push rax
    popfq
    pushfq

    push QWORD KERNEL_CODE_SELECTOR
    ; RIP
    mov rax, QWORD [rdi + 0xA8]
    push rax

    ; RBP
    mov rbp, QWORD [rdi + 0xB8]
    ; RAX/RDI
    mov rax, QWORD [rdi]
    mov rdi, QWORD [rdi + 0x28]

    iretq

user_contextSwitch:
    cmp rdi, 0x0
    je contextSwitchCrash
    mov rbx, QWORD [rdi + 0x8]
    mov rcx, QWORD [rdi + 0x10]
    mov rdx, QWORD [rdi + 0x18]
    mov rsi, QWORD [rdi + 0x20]

    mov r8,  QWORD [rdi + 0x38]
    mov r9,  QWORD [rdi + 0x40]
    mov r10, QWORD [rdi + 0x48]
    mov r11, QWORD [rdi + 0x50]
    mov r12, QWORD [rdi + 0x58]
    mov r13, QWORD [rdi + 0x60]
    mov r14, QWORD [rdi + 0x68]
    mov r15, QWORD [rdi + 0x70]

    ; SWITCH SEGMENTS
    mov ax, (USER_DATA_SELECTOR | 0x3)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; SWITCH SEGMENTS

    ; DATA SELECTOR
    push QWORD (USER_DATA_SELECTOR | 0x3)
    ; RSP
    mov rax, QWORD [rdi + 0x30]
    push rax
    ; rflags
    pushfq
    pop rax
    mov rax, QWORD [rdi + 0xB0]
    push rax

    push QWORD (USER_CODE_SELECTOR | 0x3)
    ; RIP
    mov rax, QWORD [rdi + 0xA8]
    push rax

    ; RBP
    mov rbp, QWORD [rdi + 0xB8]
    ; RAX/RDI
    mov rax, QWORD [rdi]
    mov rdi, QWORD [rdi + 0x28]

    iretq


contextSwitchCrash:
    mov rdi, contextSwitchCrashed
    call PANIC

[section .data]
    contextSwitchCrashed DB "Null pointer give at context switch..."