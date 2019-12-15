%include "boot.inc"
%include "memory.inc"

bits 64

extern kernel_setup

kernel_setup:
    add rbx, KERNEL_VIRT_BASE ; address struct multiboot
    push rbx
    hlt

; extern idt_setup
; extern load_idt
; extern init_serial_port
; extern init_vga
; extern PIC_remap
; extern init_keyboard
; extern init_timer
; extern init_mouse
; extern map_memory
; extern init_pmm
; extern init_vmm
; extern init_PCI
; extern init_rtl8139
; extern user_space
;
;     mov ebx, DWORD [rsp] ; address struct multiboot
;     push rbx
;
;     ; interruption and isr setup
;     call idt_setup
;     call load_idt
;
;     ; serial port managing
;     call init_serial_port
;
;     ; VGA driver init
;     call init_vga
;
;     ; PIC init
;     call PIC_remap
;
;     ; keyboard driver init
;     call init_keyboard
;
;     ; init basic timer
;     mov rdi, 1000 ; Hz freq divisor
;     call init_timer
;
;     ; init PS2 mouse
;     call init_mouse
;
;     pop rdi ; adress struct multiboot
;     call map_memory
;
;     ; init the physical memory managing
;     mov rdi, 0x40
;     call init_pmm
;
;     ;init the PCI (use to init and managing device's)
;     call init_PCI
;
;     ; int the RTL8139 card
;     ; call init_rtl8139
;
;     ; fire interaction with user
;     sti
;     call user_space
;
;     ; debug space
;     cli
;     mov rax, 0x2f592f412f4b2f4f ; print OKAY on screen
;     mov QWORD [0xb8000], rax
;     hlt
;     ret
