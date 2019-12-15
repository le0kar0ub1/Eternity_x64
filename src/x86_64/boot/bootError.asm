; %include "boot.inc"
;
; global no_sse
; global no_long_mode
; global no_cpuid
; global no_multiboot
;
; [section .text]
; no_sse:
;     mov al, "3"
;     jmp error
;
; no_long_mode:
;     mov al, "2"
;     jmp error
;
; no_cpuid:
;     mov al, "1"
;     jmp error
;
; no_multiboot:
;     mov al, "0"
;     jmp error
;
; error:
;     mov DWORD [0xb8000], 0x4f524f45 ; print error with vga buffer (0xb8000)
;     mov DWORD [0xb8004], 0x4f3a4f52
;     mov DWORD [0xb8008], 0x4f204f20
;     mov BYTE [0xb800a], al
;     hlt
