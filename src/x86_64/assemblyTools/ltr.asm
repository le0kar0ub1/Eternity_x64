%include "descriptors.inc"

bits 64

global flush_tss

[section .text]
flush_tss:
    mov rax, rdi
    ltr ax
    ret
