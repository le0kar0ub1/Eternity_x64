#ifndef _RFLAGS_H
#define _RFLAGS_H

#include "typedef.h"

#define CF      (1 <<  0)  /* Carry Flag */
#define RES1    (1 <<  1)  /* Reserved */
#define PF      (1 <<  2)  /* Parity Flag */
#define RES2    (1 <<  3)  /* Reserved */
#define AF      (1 <<  4)  /* Auxiliary Carry Flag */
#define RES3    (1 <<  5)  /* Reserved */
#define ZF      (1 <<  6)  /* Zero Flag */
#define SF      (1 <<  7)  /* Sign Flag */
#define TF      (1 <<  8)  /* Trap Flag */
#define IF      (1 <<  9)  /* Interrupt Enable Flag */
#define DF      (1 << 10)  /* Direction Flag */
#define OF      (1 << 11)  /* Overflow Flag */
#define IOPLBL  (1 << 12)  /* I/O Privilege Level */
#define IOPLBH  (1 << 13)  /* I/O Privilege Level */
#define NT      (1 << 14)  /* Nested Task */
#define RES4    (1 << 15)  /* Reserved */
#define RF      (1 << 16)  /* Resume Flag */
#define VM      (1 << 17)  /* Virtual-8086 Mode */
#define AC      (1 << 18)  /* Alignment Check / Access Control */
#define VIF     (1 << 19)  /* Virtual Interrupt Flag */
#define VIP     (1 << 20)  /* Virtual Interrupt Pending */
#define ID      (1 << 21)  /* ID Flag */
#define RES5    (1 << 22)  /* Reserved  22-63 */

struct rflags {
    uint64 cf    : 1;  /* Carry Flag */
    uint64 res1  : 1;  /* Reserved */
    uint64 pf    : 1;  /* Parity Flag */
    uint64 res2  : 1;  /* Reserved */
    uint64 af    : 1;  /* Auxiliary Carry Flag */
    uint64 res3  : 1;  /* Reserved */
    uint64 zf    : 1;  /* Zero Flag */
    uint64 sf    : 1;  /* Sign Flag */
    uint64 tf    : 1;  /* Trap Flag */
    uint64 ief   : 1;  /* Interrupt Enable Flag */
    uint64 df    : 1;  /* Direction Flag */
    uint64 of    : 1;  /* Overflow Flag */
    uint64 iopbl : 2;  /* I/O Privilege Level */
    uint64 nt    : 1;  /* Nested Task */
    uint64 res4  : 1;  /* Reserved */
    uint64 rf    : 1;  /* Resume Flag */
    uint64 vm    : 1;  /* Virtual-8086 Mode */
    uint64 ac    : 1;  /* Alignment Check / Access Control */
    uint64 wif   : 1;  /* Virtual Interrupt Flag */
    uint64 vip   : 1;  /* Virtual Interrupt Pending */
    uint64 id    : 1;  /* ID Flag */
    uint64 res5  : 41; /* Reserved */
} __aligned;

#endif