%include "descriptors.inc"

bits 64

global flush_tss

[section .text]
flush_tss:
    mov ax, TSS_SELECTOR
    ltr ax
    ret
