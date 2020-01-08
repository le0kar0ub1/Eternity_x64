%include "memory.inc"
%include "boot.inc"

[extern tss_size]

[global gdt]
[global gdt_start]

[global gdtKernelCode]
[global gdtKernelData]
[global gdtUserCode]
[global gdtUserData]
[global gdtTSS]

[global gdt_end]
[global gdtptr]
[global gdt_size]

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
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 10011010b                 ; Access (exec/read).
    db 10101111b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).

gdtKernelData: equ $ - gdt_start ; The Kernel data descriptor.
    dw 0xFFFF                    ; Limit (low).
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
    db 00100000b                 ; Granularity, 64 bits flag, limit19:16.
    db 0                         ; Base (high).

gdtUserData: equ $ - gdt_start   ; The user data descriptor.
    dw 0xFFFF                    ; Limit (low).
    dw 0                         ; Base (low).
    db 0                         ; Base (middle)
    db 11110010b                 ; Access (read/write).
    db 10100000b                 ; Granularity.
    db 0     

; TSS is quite different from other descriptors (base is the address of our TSS)
gdtTSS: equ $ - gdt_start
    dw tss_size                 ; Limit
	dw 0x0                      ; Base (bytes 0-2)
	db 0x0                      ; Base (byte 3)
	db 10001001b                ; Type, present
	db 10000000b                ; Misc
	db 0x0                      ; Base (byte 4)
	dd 0x0                      ; Base (bytes 5-8)
	dd 0x0                      ; Zero / reserved

    ; NULL SELECTOR
    dd 0x0
    dd 0x0
gdt_end:
gdt_size: equ gdt_end - gdt_start