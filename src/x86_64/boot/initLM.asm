bits 64

extern stack_top
extern kernel_setup

global initLM

[section .text]
set_seg_reg:
    mov ax, 0x0 ;GDT_start.KernelData
    mov ds, ax              ; data segment
    mov es, ax              ; extra segment
    mov fs, ax              ; F-segment
    mov gs, ax              ; G-segment
    mov ss, ax              ; stack segment
    ret

initLM:
    call set_seg_reg
    mov rsp, stack_top      ; re-inp the stack address
    lea rax, [kernel_setup] ; absolute address
    call rax                ; then jump in highe half virtual memory
