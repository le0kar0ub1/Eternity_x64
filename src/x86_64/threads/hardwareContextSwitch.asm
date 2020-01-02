extern PANIC

global kernel_contextSwitch
global user_contextSwitch

bits 64

[section .text]
kernel_contextSwitch:
    cmp rdi, 0x0
    je contextSwitchCrash
    mov rbx, QWORD [rdi + 0x8]
    mov rcx, QWORD [rdi + 0x10]
    mov rdx, QWORD [rdi + 0x18]
    mov rsi, QWORD [rdi + 0x20]

    mov r8,  QWORD [rdi + 0x30]
    mov r9,  QWORD [rdi + 0x38]
    mov r10, QWORD [rdi + 0x40]
    mov r11, QWORD [rdi + 0x48]
    mov r12, QWORD [rdi + 0x50]
    mov r13, QWORD [rdi + 0x58]
    mov r14, QWORD [rdi + 0x60]
    mov r15, QWORD [rdi + 0x68]

    ; SWITCH SEGMENTS
    ; mov ax, 0x10
    ; mov ds, ax
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax
    ; SWITCH SEGMENTS

    ; RFLAG
    ; mov rax, QWORD [rdi + 0xA0]
    ; push rax
    ; popfq

    push 0x10

    ; RSP
    mov rax, QWORD [rdi + 0x28]
    push rax
    ; flags
    pushfq

    push QWORD 0x8

    ; RIP
    mov rax, QWORD [rdi + 0x98]
    push rax

    ; RBP
    mov rbp, QWORD [rdi + 0xA8]

    ; RAX/RDI
    mov rax, QWORD [rdi]
    mov rdi, QWORD [rdi + 0x28]

    sti
    iret

user_contextSwitch:
    ret


contextSwitchCrash:
    mov rdi, 0x0
    call PANIC

; used during the switch to keep fatal data
[section .data]
    SWITCH_KEEP_RBP DQ 0x0
    SWITCH_KEEP_RSP DQ 0x0
