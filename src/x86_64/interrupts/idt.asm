%include "contextSwitch.inc"
%include "boot.inc"
%include "interrupt.inc"

bits 64

global idt_setup
global idtptr
global register_int_handler

extern default_int_handler

[section .text]
; used to register known particular interrupt handler to overhead default
register_int_handler:
    baseRegPush
    mov rbx, idt
    add rbx, (rdi * IDT_ENTRY_SIZE) ; go to int number

    mov rbx, idt                ; fill in 64b idt with isr address
    mov WORD [rdi], bx          ; low 16 bits
    shr rbx, 0x10
    mov WORD [rdi + 0x6], bx    ; middle/low 16 bits
    shr rbx, 0x10
    mov DWORD [rdi + 0x8], ebx  ; high 32 bits

    baseRegPop
    ret

idt_setup:
    baseRegPush
    mov rsi, default_int_handler
    mov rdi, idt
    mov rcx, IDT_ENTRY_NBR

handler_in_idt:
    mov rbx, rsi                ; fill in 64b idt with isr address
    mov WORD [rdi], bx          ; low 16 bits
    shr rbx, 0x10
    mov WORD [rdi + 0x6], bx    ; middle/low 16 bits
    shr rbx, 0x10
    mov DWORD [rdi + 0x8], ebx  ; high 32 bits

    add rsi, 0x9  ; Size of an isr (pushq + pushq + jmp)
    add rdi, IDT_ENTRY_SIZE ; size of idt
    dec rcx
    cmp rcx, 0x0
    jne handler_in_idt

    baseRegPop
    ret

[section .data]
idt:
idt_start:
    %rep 256
        dw 0x0          ; offset Low 16 bits of ISR
        dw KERNEL_CODE_SELECTOR
        db 0x0          ; IST (Interrupt stack table offset)
        db 0x8E         ; Present, ring-0, 32-bits interrupt gate
        dw 0x0          ; offset middle 16 bits of ISR
        dd 0x0          ; offset high 32 bits of ISR
        dd 0x0          ; reserved
    %endrep
idt_end:

[section .rodata]
align 16
idtptr:
    dw idt_end - idt_start - 1
    dq idt
