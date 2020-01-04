#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include "eternity.h"
#include "atomic.h"

typedef uint spinlockState;

#define SPINLOCK_LOCK   0x0
#define SPINLOCK_UNLOCK 0x1

struct spin_rwlock
{
    int volatile readcount;
    spinlockState resource_access;
    spinlockState readcount_access;
    spinlockState service_queue;
};

/* SPINLOCK MANAGING WITH ATOMIC EXCHANGE */
/* OSDEV WIKI FOR MORE INFORMATION */
static inline void spinlock_init(spinlockState *state)
{
    *state = SPINLOCK_LOCK;
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