bits 64

global tlbFlush

[section .text]
; reset TLB
tlbFlush:
    mov rax, cr3
    mov cr3, rax
