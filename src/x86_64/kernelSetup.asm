%include "boot.inc"
%include "memory.inc"
%include "contextSwitch.inc"

bits 64

extern helloFromEternity

extern idt_setup
extern load_idt
extern init_handler
extern init_serial
extern init_vga
extern remap_PIC
extern init_keyboard

global kernel_setup

kernel_setup:
    add rbx, KERNEL_VIRT_BASE ; address struct multiboot
    push rbx

    ; interruption and isr setup
    call idt_setup
    call load_idt
    call init_handler

    ; serial port managing
    call init_serial

    ; VGA driver init
    call init_vga

    ; print hello from eternity
    call helloFromEternity

    ; PIC init
    call remap_PIC

    ; keyboard driver init
    call init_keyboard

    sti
kd:
    hlt
    jmp kd

    cli
    mov rax, 0x2f592f412f4b2f4f ; print OKAY on screen
    mov QWORD [0xb8000], rax
    hlt
