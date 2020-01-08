bits 64

global tss
global tss_size
global interrupt_stack_table

[section .data]
align 16
tss:
    DD 0x0 ; Reseved 1
tss_rspn:
    DQ rspn_stack ; RSP0
    DQ rspn_stack ; RSP1
    DQ rspn_stack ; RSP2
    DQ 0x0 ; Reserved
interrupt_stack_table:
    DQ istn_stack ; IST1
    DQ istn_stack ; IST2
    DQ istn_stack ; IST3
    DQ istn_stack ; IST4
    DQ istn_stack ; IST5
    DQ istn_stack ; IST6
    DQ istn_stack ; IST7
    DQ 0x0 ; Reserved
    DW 0x0 ; Reserved
    DW tss_size ; I/O Map Base Address
tss_size: equ $ - tss - 1

[section .bss]
istn_stack: RESB 0x1000
rspn_stack: RESB 0x1000