global spinlock_lock
global spinlock_unlock
global spinlockJmp

bits 64

[section .text]
spinlock_lock:
    mov rbx, [rsp + 0x8]
    mov rax, [rbx + 0x8]
    ret
spinlockJmp:
    lock bts QWORD [rax], 0x0
    pause
    jc spinlockJmp
    ret

spinlock_unlock:
    mov rbx, [rsp + 0x8]
    mov rax, [rbx + 0x8]
    mov QWORD [rax], 0x0
    ret
