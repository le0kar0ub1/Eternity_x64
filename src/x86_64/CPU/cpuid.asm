%include "cpuid.inc"

bits 64

extern kalloc

global cpuVendorId
global logicalCPUnumber

[section .text]
; get the CPU Vendor ID
cpuVendorId:
    mov rax, 0x0
    cpuid
    mov rdi, 20
    call kalloc
    mov r10, rax

    mov r8, 0x4
    CPUvendorPart1:
        mov BYTE [rax], bl
        inc rax
        shr rbx, 0x8
        dec r8
        cmp r8, 0x0
        jne CPUvendorPart1

        mov r8, 0x4
    CPUvendorPart2:
        mov BYTE [rax], dl
        inc rax
        shr rdx, 0x8
        dec r8
        cmp r8, 0x0
        jne CPUvendorPart2

        mov r8, 0x4
    CPUvendorPart3:
        mov BYTE [rax], cl
        inc rax
        shr rcx, 0x8
        dec r8
        cmp r8, 0x0
        jne CPUvendorPart3

    mov BYTE [rax], 0x0
    mov rax, r10
    ret


; Get Features From CPUID
cpuCheckHTT:
    mov rax, 0x1
    cpuid
    ; and rdx, CPUID_FEAT_EDX_HTT
    mov rax, rdx
    ret

logicalCPUnumber:
    mov rax, 0x1
    cpuid
    call cpuCheckHTT
    ret
    shr rbx, 0x10
    and rbx, 0b1111111
    mov rax, rbx
    ret
