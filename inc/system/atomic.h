#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#include "typedef.h"
#include "assembly_inlineInstruction.h"

static inline uint atomic_exchange(volatile uint *ptr, uint value)
{
    return (xchg(ptr, value));
}

#endif