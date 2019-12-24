global init_syscall

extern syscall_handler
extern register_int_handler

[section .text]
init_syscall:
    mov rdi, 0x80
    mov rsi, syscall_handler
    call register_int_handler
    ret
