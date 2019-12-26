%include "memory.inc"
%include "boot.inc"

[global gdt]
[global gdt_start]

[global gdtKernelCode]
[global gdtKernelData]
[global gdtUserCode]
[global gdtUserData]
[global gdtTSS]

[global gdt_end]
[global gdtptr]

[section .rodata]
gdtptr:
    dw gdt_end - gdt_start - 0x1
    dd V2P(gdt)

[section .data]
align 16
gdt:
gdt_start:
    ; NULL SELECTOR
    dd 0x0
    dd 0x0

gdtKernelCode: equ $ - gdt_start ; The Kernel code descriptor.
    dw 0xFFFF                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).

gdtKernelData: equ $ - gdt_start ; The Kernel data descriptor.
    dw 0xFFFF                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10010010b                 ; Access (read/write).
    db 00000000b                 ; Granularity.
    db 0                         ; Base (high).

gdtUserCode: equ $ - gdt_start   ; The User code descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0x0                       ; Base (low).
    db 0x0                       ; Base (middle)
    db 11111010b                 ; Access (exec/read).
    db 11001111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).

gdtUserData: equ $ - gdt_start   ; The user data descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11110010b                 ; Access (read/write).
    db 11001111b                 ; Granularity.
    db 0                         ; Base (high).

gdtTSS: equ $ - gdt_start
    db 0x0
    dw 0x0000       ; limit 15:0
    dw 0x0000       ; base 15:0
    db 0x00         ; base 23:16
    db 11101001b    ; P(1) DPL(11) 0 C(1) E(0) W(0) 1
    db 10000000b    ; G(1) 00 AVL(0) limit 19:16
    db 0x00         ; base 31:24

    ; NULL SELECTOR
    dd 0x0
    dd 0x0
gdt_end: