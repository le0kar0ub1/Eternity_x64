%include "boot.inc"

extern no_sse
extern no_long_mode
extern no_cpuid
extern no_multiboot

global check_cpuid
global check_long_mode
global check_sse
global check_multiboot

bits 32

[section .text]
; check_cpuid:
;     pushfd   ; keep flags
;     pop eax
;     mov ecx, eax
;
;     xor eax, 1 << 21
;     push eax
;     popfd
;     pushfd
;     pop eax
;
;     ; Restore flags
;     push ecx
;     popfd
;
;     cmp eax, ecx
;     je no_cpuid
;     ret
;
;
; check_long_mode:
;     mov eax, 0x80000000
;     cpuid
;     cmp eax, 0x80000001
;     jb no_long_mode
;
;     mov eax, 0x80000001
;     cpuid
;     test edx, 1 << 29
;     jz no_long_mode
;     ret
;
; check_sse:
;     mov eax, 0x1
;     cpuid
;     test edx, 1 << 25
;     jz no_sse
;     ; if present, enable now
;     mov eax, cr0
;     and ax, 0xFFFB   ;clear coprocessor emulation CR0.EM
;     or ax, 0x2       ;set coprocessor monitoring  CR0.MP
;     mov cr0, eax
;     mov eax, cr4
;     or ax, 3 << 9    ;set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
;     mov cr4, eax
;     ret
;
; ; enable_avx:
; ;     push eax
; ;     push ecx
; ;
; ;     xor ecx, ecx
; ;     xgetbv ;Load XCR0 register
; ;     or eax, 7 ;Set AVX, SSE, X87 bits
; ;     xsetbv ;Save back to XCR0
; ;
; ;     pop ecx
; ;     pop eax
; ;     ret
