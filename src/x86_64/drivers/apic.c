#include "eternity.h"
#include "cpuid.h"
#include "msr.h"
#include "apic.h"
#include "interrupt.h"

static uchar *apic = NULL;

static inline void apic_write(enum apic_reg reg, uint32 value)
{
    *((volatile uint32 *)(apic + reg)) = value;
}

static inline uint32 apic_read(enum apic_reg reg)
{
    return (*((volatile uint32 *)(apic + reg)));
}

void checkApic(void)
{
    uint64 rcx, rdx;

    execpuid(0x1, &rcx, &rdx);
    if (!(rcx & CPUID_ECX_APIC))
        PANIC("APIC must be usable to run eternity\n");
}

void init_apic(void)
{
    uint64 msr;

    checkApic();
    fatalAssert(apic);

    /* Enable Local APIC by setting spurious interrupt vector */
    apic_write(APIC_SIV, APIC_SVR_ENABLED | INT_APIC_SPURIOUS);

    /* Mask unused/unsupported interrupts */
    apic_write(APIC_LVT_LINT0, APIC_LVT_MASKED);
    apic_write(APIC_LVT_LINT1, APIC_LVT_MASKED);
    apic_write(APIC_LVT_PERFCOUNT, APIC_LVT_MASKED);

    /* Set up apic Timer */
    apic_write(APIC_TIMER_DCR, APIC_TIMER_X8);
    apic_write(APIC_LVT_TIMER, APIC_TIMER_PERIODIC | INT_APIC_TIMER);
    apic_write(APIC_TIMER_ICR, 10000000);

    /* Map error interrupt */
    apic_write(APIC_LVT_ERROR, INT_APIC_ERROR);

    /* IRQs */
    // register_int_handler(INT_APIC_TIMER, &apic_timer_ihandler);
    // register_int_handler(INT_APIC_ERROR, &apic_error_ihandler);
    // register_int_handler(INT_APIC_SPURIOUS, &apic_spurious_ihandler);

    /* Clear Error Status Register */
    apic_write(APIC_ESR, 0x0);
    apic_write(APIC_ESR, 0x0);

    /* Clear any outstanding interrupts */
    apic_write(APIC_EOI, 0x0);

    /* Clear task priority to enable all interrupts */
    apic_write(APIC_TPR, 0x0);

    /* Enable APIC in the MSR */
    msr = read_msr(MSR_APIC_BASE);
    msr |= (1 << 11u);
    write_msr(MSR_APIC_BASE, msr);
}
