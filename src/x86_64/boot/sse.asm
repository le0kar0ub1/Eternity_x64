%include "memory.inc"

global check_enable_sse

bits 32

[section .text]
check_enable_sse:
    mov eax, 0x1
    cpuid
    test edx, 1 << 25
    jz no_sse
    ; if present, enable now
    mov eax, cr0
    and ax, 0xFFFB   ;clear coprocessor emulation CR0.EM
    or ax, 0x2       ;set coprocessor monitoring  CR0.MP
    mov cr0, eax
    mov eax, cr4
    or ax, 0x3 << 0x9    ;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
    mov cr4, eax

    fxsave [V2P(float_mem)] ; load address float space
no_sse:
    ret

[section .data]
align 16
float_mem: TIMES 512 DB 0 ; Space for save floats
