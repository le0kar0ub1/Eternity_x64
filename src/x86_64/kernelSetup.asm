%include "boot.inc"
%include "memory.inc"
%include "contextSwitch.inc"

bits 64

extern idt_setup
extern load_idt

global kernel_setup

kernel_setup:
    add rbx, KERNEL_VIRT_BASE ; address struct multiboot
    push rbx

    ; interruption and isr setup
    call idt_setup
    call load_idt

    cli
    mov rax, 0x2f592f412f4b2f4f ; print OKAY on screen
    mov QWORD [0xb8000], rax
    hlt
