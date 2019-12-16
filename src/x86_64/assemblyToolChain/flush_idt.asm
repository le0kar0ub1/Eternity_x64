%include "descriptors.inc"

bits 64

global flush_idt

[section .text]
flush_idt:
    mov rax, rdi
    lidt [rax]
    ret
