bits 64

global flush_tss

[section .text]
flush_tss:
    mov ax, 0x2B
    ltr ax
    ret
