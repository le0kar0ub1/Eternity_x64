%include "boot.inc"
%include "memory.inc"

bits 32

[global _start]
[global kernel_stack]

[extern gdtptr]
[extern gdtKernelCode]
[extern gdt]
[extern initLM]
[extern check_enable_sse]

[section .text]
_start:
    cli
    mov esp, V2P(kernel_stack)

    push ebx ; address struct multiboot

    ; sanity checkup
    call check_multiboot
    call check_cpuid
    call check_long_mode

    ; sse check and enable if possible
    call check_enable_sse

    ; memory mapping
    call vmm_pmm_mapping
    call enable_paging

    ; gdt loading
    mov eax, V2P(gdtptr)
    lgdt [eax]

    pop ebx ; address struct multiboot
    ; far jump & load kernel code gdt
    jmp gdtKernelCode:V2P(initLM)
    mov esi, V2P(jumpFailed)
    call EARLY_CRASH
    hlt

vmm_pmm_mapping:
    mov eax, V2P(PDPT)
    or eax, (MMU_PRESENT | MMU_WRITABLE | MMU_USER_MEMORY)
    mov DWORD [V2P(PML4)], eax
    mov DWORD [V2P(PML4) + (PML4_ENTRY_INDEX * PAGE_ENTRY_SIZE)], eax

    mov eax, V2P(PDT)
    or eax, (MMU_PRESENT | MMU_WRITABLE | MMU_USER_MEMORY)
    mov DWORD [V2P(PDPT)], eax
    mov DWORD [V2P(PDPT) + (PDPT_ENTRY_INDEX * PAGE_ENTRY_SIZE)], eax

    xor ecx, ecx
    mapping_loop:
        mov eax, 0x200000 ; 2 MIB page
        mul ecx
        or eax, (MMU_PRESENT | MMU_WRITABLE | MMU_USER_MEMORY | MMU_PDE_TWO_MB)
        mov DWORD [V2P(PDT) + (ecx * PAGE_ENTRY_SIZE)], eax
        inc ecx
        cmp ecx, PAGE_ENTRY
        jne mapping_loop
    ret

enable_paging:
    mov eax, V2P(PML4)
    mov cr3, eax

    ; PAE flag & global flag
    mov eax, cr4
    or eax, (0x1 << 0x5) | (1 << 7)
    mov cr4, eax

    ; set long mode in EFER MSR & NXE
    mov ecx, 0xC0000080
    rdmsr
    or eax, (0x1 << 0x8) | (0x1 << 0xB)
    wrmsr

    ; protected mode & paging
    mov eax, cr0
    or eax, (1 << 31) | (1 << 16) | (1 << 0)
    mov cr0, eax

    ; flushing that
    mov eax, cr3
	mov cr3, eax
    ret

[section .bss]
align 1024
stack_bottom:
    RESB KERNEL_STACK_SIZE
kernel_stack:

global PML4
global PDPT
global PDT
[section .bss]
align 0x1000
PML4:
    RESB 0x1000
PDPT:
    RESB 0x1000
PDT:
    RESB 0x1000

; error debug information
[section .rodata]
    noMultiboot   db 'No multiboot detected', 0x0
    noCPUID       db 'No CPUID detected', 0x0
    longModeError db 'No long mode', 0x0
    jumpFailed    db 'Far jumb failed', 0x0

[section .text]
; print error to screen
directPrint:
    push edi
    push eax
    mov edi, 0xb8000

    directPrintLoop:
        mov al, BYTE [esi]
        cmp al, 0x0
        je endDirectPrintLoop
        mov BYTE [edi + 1], 0x4F
        mov BYTE [edi], al
        inc esi
        add edi, 0x2
        jmp directPrintLoop
    endDirectPrintLoop:

    pop eax
    pop edi
    ret

; crash in early step
EARLY_CRASH:
    call directPrint
    hlt
    ret

; sanity checks multiboot
check_multiboot:
    cmp eax, MAGIC_BOOTLOADER_MB2
    je multibootDetect
    mov esi, V2P(noMultiboot)
    call EARLY_CRASH
multibootDetect:
    ret

; sanity check cpuid detect
check_cpuid:
    pushfd   ; keep flags
    pop eax
    mov ecx, eax

    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    ; Restore flags
    push ecx
    popfd
    cmp eax, ecx
    jne cpuidDetect

    mov esi, V2P(noCPUID)
    call EARLY_CRASH
cpuidDetect:
    ret

check_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb longModeError

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz longModeError
    ret
    noLongMode:
        mov esi, V2P(longModeError)
        call EARLY_CRASH
