global spinLock_acquireLock
global spinLock_releaseLock

bits 64

[section .text]
spinLock_acquireLock:
    lock bts QWORD [rdi], 0x0        ;Attempt to acquire the lock (in case lock is uncontended)
    jc .spin_with_pause
    ret
 
.spin_with_pause:
    pause                      ; Tell CPU we're spinning
    test QWORD [rdi], 0x1      ; Is the lock free?
    jnz .spin_with_pause       ; no, wait
    jmp spinLock_acquireLock   ; retry
 
spinLock_releaseLock:
    mov QWORD [rdi], 0x0
    ret