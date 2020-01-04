%include "boot.inc"
%include "memory.inc"
%include "contextSwitch.inc"
%include "descriptors.inc"

bits 64

extern helloFromEternity

extern idt_setup
extern load_idt
extern init_handler
extern init_tss
extern init_serial
extern init_vga
extern init_pic
extern init_pf_handler
extern init_pmm
extern init_kpaging
extern init_vmm
extern init_kalloc
extern init_timer
extern init_keyboard
extern init_pci
extern init_rtc
extern init_threads
extern init_syscall

extern fire_userspace

extern init_tty

extern kmain

global kernel_setup

[section .text]
kernel_setup:
    add rbx, KERNEL_VIRT_BASE ; address struct multiboot
    push rbx

    ; interruption & isr & handler setup
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
    call init_pic

    ; pop rdi
    ; extern get_multiboot_tag
    ; call get_multiboot_tag

    ; register page fault handler
    call init_pf_handler

    ; init phys memory manager
    call init_pmm

    ; init new kpaging with static/dynamic part
    call init_kpaging

    ; init vmm
    call init_vmm

    ; init kheap allocation
    call init_kalloc

    ; init PIT timer
    call init_timer

    ; keyboard driver init
    call init_keyboard

    ; init pci
    call init_pci

    ; init CMOS RTC
    call init_rtc

    ; tss init
    call init_tss

    ; init syscall handler
    call init_syscall


    call kmain

    ; print 'OKAY' if all comes good
    cli
    mov rax, 0x2f592f412f4b2f4f
    mov QWORD [0xb8000], rax
    hlt
