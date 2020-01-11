%include "descriptors.inc"
%include "rflags.inc"

bits 64

extern PANIC

global kernel_contextSwitch
global user_contextSwitch

[section .text]
kernel_contextSwitch:
    cmp rdi, 0x0
    je contextSwitchCrash
    ; SWITCH SEGMENTS
    mov ax, KERNEL_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov r15, QWORD [rdi + 0x20]
    mov r14, QWORD [rdi + 0x28]
    mov r13, QWORD [rdi + 0x30]
    mov r12, QWORD [rdi + 0x38]
    mov r11, QWORD [rdi + 0x40]
    mov r10, QWORD [rdi + 0x48]
    mov r9,  QWORD [rdi + 0x50]
    mov r8,  QWORD [rdi + 0x58]

    mov rcx, QWORD [rdi + 0x68]
    mov rdx, QWORD [rdi + 0x70]
    mov rbx, QWORD [rdi + 0x78]
    mov rsi, QWORD [rdi + 0x80]


    ; DATA SELECTOR
    push QWORD KERNEL_DATA_SELECTOR
    ; RSP
    mov rax, QWORD [rdi + 0xC0]
    push rax
    ; rflags
    mov rax, QWORD [rdi + 0xB8]
    push rax
    popfq
    pushfq

    push QWORD KERNEL_CODE_SELECTOR
    ; RIP
    mov rax, QWORD [rdi + 0xA8]
    push rax

    ; RBP
    mov rbp, QWORD [rdi + 0x90]
    ; RAX/RDI
    mov rdi, QWORD [rdi + 0x88]

    ; PIC EOI
    mov al, 0xA0
    out 0x20, al
    mov rax, QWORD [rdi + 0x60]
    iretq

user_contextSwitch:
    cmp rdi, 0x0
    je contextSwitchCrash
    ; SWITCH SEGMENTS
    mov ax, (USER_DATA_SELECTOR | 0x3)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov r15, QWORD [rdi + 0x20]
    mov r14, QWORD [rdi + 0x28]
    mov r13, QWORD [rdi + 0x30]
    mov r12, QWORD [rdi + 0x38]
    mov r11, QWORD [rdi + 0x40]
    mov r10, QWORD [rdi + 0x48]
    mov r9,  QWORD [rdi + 0x50]
    mov r8,  QWORD [rdi + 0x58]

    mov rcx, QWORD [rdi + 0x68]
    mov rdx, QWORD [rdi + 0x70]
    mov rbx, QWORD [rdi + 0x78]
    mov rsi, QWORD [rdi + 0x80]


    ; DATA SELECTOR
    push QWORD (USER_DATA_SELECTOR | 0x3)
    ; RSP
    mov rax, QWORD [rdi + 0xC0]
    push rax
    ; rflags
    mov rax, QWORD [rdi + 0xB8]
    or rax, IOPLBL | IOPLBH
    push rax
    popfq
    pushfq

    push QWORD (USER_CODE_SELECTOR | 0x3)
    ; RIP
    mov rax, QWORD [rdi + 0xA8]
    push rax

    ; RBP
    mov rbp, QWORD [rdi + 0x90]
    ; RAX/RDI
    mov rdi, QWORD [rdi + 0x88]

    ; PIC EOI
    mov al, 0xA0
    out 0x20, al
    mov rax, QWORD [rdi + 0x60]
    iretq


contextSwitchCrash:
    mov rdi, contextSwitchCrashed
    call PANIC

[section .data]
    contextSwitchCrashed DB "Null pointer give at context switch..."