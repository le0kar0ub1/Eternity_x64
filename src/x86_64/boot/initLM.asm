bits 64

extern kernel_stack
extern kernel_setup

global initLM

[section .text]
set_seg_reg:
    mov ax, 0x10 ;GDT_start.KernelData
    mov ds, ax              ; data segment
    mov es, ax              ; extra segment
    mov fs, ax              ; F-segment
    mov gs, ax              ; G-segment
    mov ss, ax              ; stack segment
    ret

initLM:
    call set_seg_reg
    mov rsp, kernel_stack      ; re-inp the stack address
    lea rax, [kernel_setup] ; absolute address
    call rax                ; then jump in highe half virtual memory
