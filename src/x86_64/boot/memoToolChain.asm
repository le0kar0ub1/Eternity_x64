%include "memory.inc"
%include "boot.inc"

bits 32

[section .text]
; reset TLB
tlbFlush:
    mov eax, cr3
    mov cr3, eax
