%ifndef _MEMORY_INC_
%define _MEMORY_INC_

; QEMU MONITOR : https://en.wikibooks.org/wiki/QEMU/Monitor

%define PDE_INDEX        (KERNEL_VIRT_BASE >> 22)

; identity paging at start
%define PAGE_SIZE        0x1000
%define PAGE_ENTRY       0x200
%define PAGE_ENTRY_SIZE  0x8
%define SIZEOF_ENTRY     (PAGE_SIZE / PAGE_ENTRY)

%define TWO_MEGABYTES_SHIFT 21
%define TWO_MEGABYTES       (1 << TWO_MEGABYTES_SHIFT)

%define KERNEL_PHYS_START 0x0000000000400000
%define KERNEL_VIRT_START 0xFFFFC00000100000

%define PML4_ADDR_TO_INDEX(addr) ((addr >> 39) & 0x1FF) ; skip 39 first bits & set the rest
%define PDPT_ADDR_TO_INDEX(addr) ((addr >> 30) & 0x1FF) ; skip 30 first bits & set the rest
%define MMU_PRESENT     (1 << 0)
%define MMU_WRITABLE    (1 << 1)
%define MMU_USER_MEMORY (1 << 2)
%define MMU_PDE_TWO_MB  (1 << 7)

; limits
%define MAX_ADDR_32B_SYS 0xFFFFFFFF
%define MAX_ADDR_64B_SYS 0xFFFFFFFFFFFFFFFF

; Descriptor Privilege Level
%define DPL0             0x0
%define DPL1             0x1
%define DPL2             0x2
%define DPL3             0x3

; CR0 bits
%define PE  0x0
%define MP  0x1
%define EM  0x2
%define TS  0x3
%define ET  0x4
%define NE  0x5
%define WP  0x10
%define AM  0x12
%define PG  0x1F

%endif
