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

    /* enable syscall in EFER */
    uint64 rd = rdmsr(0xC0000080);
    rd |= 0x1 << MSR_SCE; // syscall enable
    wrmsr(0xC0000080, rd);

    /* insert KERNEL CODE SELECTOR */
    /* user code selector must be at + 16 */
    wrmsr(MSR_IA32_SYSENTER_CS, KERNEL_CODE_SELECTOR);
    /* insert STACK ADDRESS */
    uint64 stack = (uint64)kalloc(0x4000);
    wrmsr(MSR_IA32_SYSENTER_RSP, stack);
    /* insert SYSCALL HANDLER entry point */
    wrmsr(MSR_IA32_SYSENTER_RIP, (uint64)syscall_handler);
    
    /* depreceated  in 64 bits */
    register_int_handler(0x80, syscall_handler);
}