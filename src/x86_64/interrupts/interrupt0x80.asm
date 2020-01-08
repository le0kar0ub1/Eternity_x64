%include "syscall.inc"

bits 64

global init_int0x80

extern syscall_table
extern syscallCrashed
extern register_int_handler

[section .text]
; register it in handler list table
init_int0x80:
    mov rdi, 0x80
    mov rsi, int0x80_handler
    call register_int_handler
    ret

int0x80_handler:
    mov rax, QWORD [rdi + 48] ; struct frame skip
    cmp rax, x86_MAX_SYSCALL
    jae syscallCrashed

    mov rax, QWORD [syscall_table + (rax * 0x8)] ; pointer on handler
    cmp rax, 0x0
    je syscallCrashed

    ; call the handler
    call rax

    ret