#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include "eternity.h"
#include "atomic.h"

typedef bool spinlockState

#define SPINLOCK_LOCK   0x0
#define SPINLOCK_UNLOCK 0x1

static inline void spinlock_init(spinlockState *state)
{
    *state = SPINLOCK_DEFAULT;
}

static inline void spinlock_acquire(spinlockState *state)
{
    while (atomic_exchange(state, SPINLOCK_UNLOCK) != 0);
}

static inline void spinlock_release(spinlockState *state)
{
    atomic_exchange(state, SPINLOCK_LOCK);
}

#endif