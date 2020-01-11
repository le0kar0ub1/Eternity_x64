#include "eternity.h"

#ifndef _INTERRUPTS_HANDLER_H_
#define _INTERRUPTS_HANDLER_H_

/*  x86_64 interrupts vectors */
enum x86_64_interrupts
{
    INT_DIVISION_BY_ZERO    = 0x0,
    INT_DEBUG               = 0x1,
    INT_NON_MASKABLE_INT    = 0x2,
    INT_BREAKPOINT          = 0x3,
    INT_OVERFLOW            = 0x4,
    INT_OUT_OF_BOUNDS       = 0x5,
    INT_INVALID_OPCODE      = 0x6,
    INT_DEVICE_NA           = 0x7,
    INT_DOUBLE_FAULT        = 0x8,
    INT_COCPU_SEG_OVERRUN   = 0x9,
    INT_INVALID_TSS         = 0xA,
    INT_SEGMENT_NOT_PRESENT = 0xB,
    INT_STACK_FAULT         = 0xC,
    INT_GP_FAULT            = 0xD,
    INT_PAGE_FAULT          = 0xE,
    INT_UNKNOW_INT          = 0xF, /* reserved */
    INT_FPU_FAULT           = 0x10,
    INT_ALIGNMENT_CHECK     = 0x11,
    INT_MACHINE_CHECK       = 0x12,
    INT_SIMD                = 0x13,
    INT_VIRT_EXECPTION      = 0x14,
    /* reserved */
    INT_SECURITY_EXECPTION  = 0x1E,
    /* reserved */
    INT_IRQ0                = 0x20,
    INT_IRQ1                = 0x21,
    INT_IRQ2                = 0x22,
    INT_IRQ3                = 0x23,
    INT_IRQ4                = 0x24,
    INT_IRQ5                = 0x25,
    INT_IRQ6                = 0x26,
    INT_IRQ7                = 0x27,
    INT_IRQ8                = 0x28,
    INT_IRQ9                = 0x29,
    INT_IRQ10               = 0x2A,
    INT_IRQ11               = 0x2B,
    INT_IRQ12               = 0x2C,
    INT_IRQ13               = 0x2D,
    INT_IRQ14               = 0x2E,
    INT_IRQ15               = 0x2F,

    INT_APIC_TIMER          = 0x32,
    INT_APIC_ERROR          = 0x33,
    INT_APIC_SPURIOUS       = 0xFF,

    INT_SYSCALL             = 0x80,

    MAX_INT                 = 0x100,
};

#define ERR_PF_PRES 0x1
#define ERR_PF_RW   0x2
#define ERR_PF_USER 0x4
#define ERR_PF_RES  0x8
#define ERR_PF_INST 0x10

/* struct describe current frame to handle the int */
struct frame {
    uintptr gs;
    uintptr fs;
    uintptr es;
    uintptr ds;

    uintptr r15;
    uintptr r14;
    uintptr r13;
    uintptr r12;
    uintptr r11;
    uintptr r10;
    uintptr r9;
    uintptr r8;

    uintptr rax;
    uintptr rcx;
    uintptr rdx;
    uintptr rbx;
    uintptr rsi;
    uintptr rdi;

    uintptr rbp;

    uintptr int_num;
    uintptr error;

    uintptr rip;
    uintptr cs;
    uintptr rflags;
    uintptr userrsp;
    uintptr ss;
};

/* declaration functions */
void syscall_handler(struct frame *frame);
void init_syscall(void);
void exceptions_handler(struct frame *frame);
void register_int_handler(int nbr, void *fnct);

#endif
