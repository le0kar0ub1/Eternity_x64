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
gdtNull: equ $ - gdt_start       ; The null descriptor.
    dw 0x0                       ; Limit (low).
    dw 0x0                       ; Base (low).
    db 0x0                       ; Base (middle)
    db 0x0                       ; Access.
    db 0x0                       ; Granularity.
    db 0x0                       ; Base (high).

gdtKernelCode: equ $ - gdt_start ; The Kernel code descriptor.
    dw 0                         ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).

gdtKernelData: equ $ - gdt_start ; The Kernel data descriptor.
    dw 0                         ; Limit (low).
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
    dw 0xFFFF
    dw 0x0
    db 0x0
    db 0x0
    db 0x0
    db 0x0
gdt_end:
