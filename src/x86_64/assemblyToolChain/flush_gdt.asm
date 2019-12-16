%include "descriptors.inc"

bits 64

global flush_gdt

[section .text]
flush_gdt:
    mov rax, rdi
    lgdt [rax]

    mov ax, KERNEL_DATA_SELECTOR
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret
