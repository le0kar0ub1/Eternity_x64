%include "descriptors.inc"

extern interrupts_handler

global isr

[section .text]
isr:
%assign i 0x0
%rep 256
    ; if interrut gen an error code
    %if i == 8 || (i >= 10 && i <= 14) || i == 17
        nop ; Two nops == one push
        nop
        ; error code already push by cpu
        push QWORD i
        jmp interrupt_catch
    %else
        push QWORD 0x0 ; Fake error code
        push QWORD i
        jmp interrupt_catch
    %endif
    %assign i (i + 1)
%endrep

interrupt_catch:
    push rbp
    push rdi    ; save base registers
    push rsi
    push rbx
    push rdx
    push rcx
    push rax
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    mov rax, ds ; Save segment registers
    push rax
    mov rax, es
    push rax
    mov rax, fs
    push rax
    mov rax, gs
    push rax

    mov rdi, rsp        ; stack pointer use for struct frame
    cld
    call swapgsCheckUp
    call interrupts_handler ; rax contain return value of syscall
    call swapgsCheckUp
    std
    mov r10, rax

    pop rax
    mov gs, rax
    pop rax
    mov fs, rax
    pop rax
    mov es, rax
    pop rax
    mov ds, rax

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    mov rax, r10    ; ret value of syscall
    pop r10
    pop r9
    pop r8
    pop rcx         ; clean rax
    pop rcx
    pop rdx
    pop rbx
    pop rsi
    pop rdi
    pop rbp

    add rsp, 0x10   ; Clean error code and int nbr
    iretq           ; Return from interrupt


swapgsCheckUp:
    cmp QWORD [rsp], 0x8
    je noSwapgs
    swapgs
noSwapgs:
    ret
