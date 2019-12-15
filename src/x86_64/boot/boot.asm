%include "boot.inc"
%include "memory.inc"

extern KERNEL_PHYS_END

global init

bits 32

[section .multiboot]
align 8
mb_header:
    dd MAGIC_HEADER_MB2
    dd PROTECTED_MODE       ; architecture 0 (protected mode i386) only 32-bit instructions and up to 4GiB memory
    dd mb_header_end - mb_header  ; mb_header length
    ; checksum
    dd - (MAGIC_HEADER_MB2 + PROTECTED_MODE + (mb_header_end - mb_header))

    dw MULTIBOOT_HEADER_TAG_END    ; type
    dw 0x0    ; flags
    dd 0x8    ; size
mb_header_end:

[section .text]
init:
    cli
    mov esp, (stack_top)

    push ebx ; address struct multiboot

check_multiboot:
    cmp eax, MAGIC_BOOTLOADER_MB2
    jne EARLY_CRASH

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
    je EARLY_CRASH

global_mmap:
    mov eax, (LPDPT)
    or eax, (MMU_PRESENT | MMU_WRITABLE)
    mov [PML4_ADDR_TO_INDEX(KERNEL_PHYS_START) * PAGE_ENTRY_SIZE], eax

    mov eax, (HPDPT)
    or eax, (MMU_PRESENT | MMU_WRITABLE)
    mov [PML4_ADDR_TO_INDEX(KERNEL_VIRT_START) * PAGE_ENTRY_SIZE], eax

    mov eax, (LPDT)
    or eax, (MMU_PRESENT | MMU_WRITABLE)
    mov [PDPT_ADDR_TO_INDEX(KERNEL_PHYS_START) * PAGE_ENTRY_SIZE], eax

    mov eax, (HPDT)
    or eax, (MMU_PRESENT | MMU_WRITABLE)
    mov [PDPT_ADDR_TO_INDEX(KERNEL_VIRT_START) * PAGE_ENTRY_SIZE], eax

    mov ecx, 0x0
    mov esi, KERNEL_PHYS_END
    shr esi, TWO_MEGABYTES_SHIFT
    inc esi
mapping_loop:
    mov eax, 0x0000000000100000;TWO_MEGABYTES
    mul ecx
    or eax, (MMU_PRESENT | MMU_WRITABLE | MMU_PDE_TWO_MB)
    mov ebx, (LPDT)
    mov [ebx + (ecx * PAGE_ENTRY_SIZE)], eax
    mov ebx, (HPDT)
    mov [ebx + (ecx * PAGE_ENTRY_SIZE)], eax
    inc ecx
    cmp ecx, esi
    jne mapping_loop

    mov eax, (PML4)
    mov cr3, eax

    mov eax, 1 << 5
    mov cr4, eax

    mov ecx, 0xC0000080
    rdmsr
    or eax, (1 << 8)
    wrmsr

    mov eax, 1 << PE
    or eax, 1 << ET
    or eax, 1 << PG
    mov cr0, eax
    hlt

[section .bss]
align 1024
stack_bottom:
    RESB KERNEL_STACK_SIZE
stack_top:

global PML4
global LPDPT
global HPDPT
global LPDT
global HPDT
[section .bss]
align 0x1000
PML4:
    RESB 0x1000
LPDPT:
    RESB 0x1000
HPDPT:
    RESB 0x1000
LPDT:
    RESB 0x1000
HPDT:
    RESB 0x1000

[section .text]
EARLY_CRASH:
    mov DWORD [0xb8000], 0x4f524f43
    mov DWORD [0xb8004], 0x4f534f41
    mov DWORD [0xb8008], 0x4f454f48
    mov WORD [0xb800C], 0x4f44
    hlt
