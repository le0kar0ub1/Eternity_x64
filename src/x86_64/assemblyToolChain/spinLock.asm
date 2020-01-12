global spin_lock
global spin_unlock
global spin_unfatal_lock

bits 64

[section .text]
spin_lock:
    lock bts QWORD [rdi], 0x0        ;Attempt to acquire the lock (in case lock is uncontended)
    jc .spin_retry
    ret
 
.spin_retry:
    pause                      ; Tell CPU we're spinning
    test QWORD [rdi], 0x1      ; Is the lock free?
    jnz .spin_retry       ; no, wait
    jmp spin_lock   ; retry
 
spin_unlock:
    mov QWORD [rdi], 0x0
    ret

; NO FATAL IF NO LOCK
; deadlock never comes with this
spin_unfatal_lock:
    lock bts QWORD [rdi], 0x0
    jc .unacquired
    mov rax, 0x1
    ret
.unacquired:
    mov rax, 0x0
    ret