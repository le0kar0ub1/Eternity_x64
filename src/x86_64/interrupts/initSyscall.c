#include "msr.h"
#include "cpuid.h"
#include "interrupt.h"
#include "descriptors.h"

void init_syscall(void)
{
    uint64 rdx, rcx; 
    execpuid(0x80000001, &rcx, &rdx);

    if (!(rdx & CPUID_EDX_SEP))
        PANIC("Syscall bad opcode during init");

    uint64 star = rdmsr(MSR_IA32_STAR);
    star &= 0x00000000ffffffff;
    star |= (uint64)KERNEL_CODE_SELECTOR << 32;
    star |= (uint64)((USER_CODE_SELECTOR - 16) | 3) << 48;
    wrmsr(MSR_IA32_STAR, star);

    // Write the address of the system call handler used by SYSCALL.
    wrmsr(MSR_IA32_LSTAR, (uint64)syscall_handler);
    hlt();

    // Write the CPU flag mask used during SYSCALL.
    wrmsr(MSR_IA32_FMASK, 0x0);
    register_int_handler(0x80, syscall_handler);
}