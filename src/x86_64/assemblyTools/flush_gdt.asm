%include "descriptors.inc"

bits 64

global flush_gdt

[section .text]
flush_gdt:
    sub rsp, 0xA
    mov WORD [rsp], si
    mov QWORD [rsp + 0x2], rdi
    lgdt [rsp]
    add rsp, 0xA
    ret
