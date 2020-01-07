%include "msr.inc"
%include "cpuid.inc"
%include "syscall.inc"

bits 64

global init_syscall
global register_syscall_handler
global syscall_table

extern syscall_register_init
extern syscall_handler
extern PANIC

[section .text]
init_syscall:
    ; Check that syscall and sysret are actually available, else crash...
    mov eax, MSR_IA32_BASE
    xor ecx, ecx
    cpuid
    test edx, CPUID_EDX_SEP
    mov rdi, initSyscallCrashed
    jz PANIC

    mov ecx, MSR_IA32_STAR
    rdmsr
    ; Load user 32-bit cs into STAR[63:48] and load kernel cs into STAR[47:32]
    mov edx, 0x00180008
    wrmsr

    mov ecx, MSR_IA32_LSTAR
    rdmsr

    ; Load rip into LSTAR
    mov rdi, syscall_handler
    mov eax, edi
    shr rdi, 0x20
    mov edx, edi
    wrmsr

    ; Enable both instructions
    mov ecx, MSR_IA32_EFER ; IA32_EFER MSR
    rdmsr
    or eax, (1 << MSR_SCE)
    wrmsr

    ; Set FMASK MSR for rflags
    mov ecx, MSR_IA32_MASK ; IA32_FMASK MSR
    rdmsr
    or eax, (1 << 9) | (1 << 10) ; Disable interrupts, clear direction flag
    wrmsr

    ; init the register with known syscall handler
    call syscall_register_init
    ret

[section .data]
    initSyscallCrashed db "System can't handle syscall...", 0xA, 0x0

[section .data]
syscall_table:
%rep x86_MAX_SYSCALL
    DQ 0x0
%endrep

[section .text]
register_syscall_handler:
    mov rdx, syscall_table
    mov rax, 0x8
    mul rdi
    add rdx, rdi
    mov QWORD [rdx], rsi
    ret