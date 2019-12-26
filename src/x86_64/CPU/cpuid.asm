%include "cpuid.inc"

bits 64

extern kalloc

global execpuid

global cpuVendorId
global logicalCPUnumber

[section .text]
execpuid:
    mov rax, rdi
    mov r8, rdx
    cpuid
    mov QWORD [rsi], rcx
    mov QWORD [r8], rdx
    ret

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
