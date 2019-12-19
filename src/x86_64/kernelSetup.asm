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
extern init_pmm
extern init_kpaging
extern init_vmm
extern init_timer

global kernel_setup

[section .text]
kernel_setup:
    add rbx, KERNEL_VIRT_BASE ; address struct multiboot
    push rbx

    ; interruption and isr setup
    call idt_setup
    call load_idt
    call init_handler

    ; serial port init
    call init_serial

    ; VGA driver init
    call init_vga

    ; print hello from eternity
    call helloFromEternity

    ; PIC init
    call remap_PIC

    ; keyboard driver init
    call init_keyboard

    ; pop rdi
    ; extern get_multiboot_tag
    ; call get_multiboot_tag

    ; init phys memory manager
    call init_pmm

    ; init new kpaging with static/dynamic
    call init_kpaging

    ; init vmm
    call init_vmm

    ; cli
    ; hlt

    sti
inf:
    hlt
    jmp inf



    ; init PIT timer
    call init_timer


    ; print if all comes good
    cli
    mov rax, 0x2f592f412f4b2f4f ; print OKAY on screen
    mov QWORD [0xb8000], rax
    hlt
