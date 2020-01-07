#ifndef _RFLAGS_H
#define _RFLAGS_H

#include "typedef.h"

// typedef uint64 rflags

#define CF         (1 <<  0)  /* Carry Flag */
#define RES1       (1 <<  1)  /* Reserved */
#define PF         (1 <<  2)  /* Parity Flag */
#define RES2       (1 <<  3)  /* Reserved */
#define AF         (1 <<  4)  /* Auxiliary Carry Flag */
#define RES3       (1 <<  5)  /* Reserved */
#define ZF         (1 <<  6)  /* Zero Flag */
#define SF         (1 <<  7)  /* Sign Flag */
#define TF         (1 <<  8)  /* Trap Flag */
#define IF         (1 <<  9)  /* Interrupt Enable Flag */
#define DF         (1 << 10)  /* Direction Flag */
#define OF         (1 << 11)  /* Overflow Flag */
#define IOPLBL     (1 << 12)  /* I/O Privilege Level */
#define IOPLBH     (1 << 13)  /* I/O Privilege Level */
#define NT         (1 << 14)  /* Nested Task */
#define RESERVED1  (1 << 15)  /* Reserved */
#define RF         (1 << 16)  /* Resume Flag */
#define VM         (1 << 17)  /* Virtual-8086 Mode */
#define AC         (1 << 18)  /* Alignment Check / Access Control */
#define VIF        (1 << 19)  /* Virtual Interrupt Flag */
#define VIP        (1 << 20)  /* Virtual Interrupt Pending */
#define ID         (1 << 21)  /* ID Flag */
#define RESERVED   (1 << 22)  /* Reserved  22-63 */

struct rflags {
    uint8 CF    : 1;  /* Carry Flag */
    uint8 RES1  : 1;  /* Reserved */
    uint8 PF    : 1;  /* Parity Flag */
    uint8 RES2  : 1;  /* Reserved */
    uint8 AF    : 1;  /* Auxiliary Carry Flag */
    uint8 RES3  : 1;  /* Reserved */
    uint8 ZF    : 1;  /* Zero Flag */
    uint8 SF    : 1;  /* Sign Flag */
    uint8 TF    : 1;  /* Trap Flag */
    uint8 IF    : 1;  /* Interrupt Enable Flag */
    uint8 DF    : 1;  /* Direction Flag */
    uint8 OF    : 1;  /* Overflow Flag */
    uint8 IOPLB : 2;  /* I/O Privilege Level */
    uint8 NT    : 1;  /* Nested Task */
    uint8 RES4  : 1;  /* Reserved */
    uint8 RF    : 1;  /* Resume Flag */
    uint8 VM    : 1;  /* Virtual-8086 Mode */
    uint8 AC    : 1;  /* Alignment Check / Access Control */
    uint8 VIF   : 1;  /* Virtual Interrupt Flag */
    uint8 VIP   : 1;  /* Virtual Interrupt Pending */
    uint8 ID    : 1;  /* ID Flag */
    uint8 RES5  : 41; /* Reserved */
} __aligned;

#endif