#ifndef _PROCESSUS_H_
#define _PROCESSUS_H_

#include "eternity.h"
#include "scheluder.h"
#include "cpuState.h"

#define SCHED_TOLERANCE 5

enum threadState {
    THREAD_RUNNING          = 0,
    THREAD_INTERRUPTIBLE    = 1,
    THREAD_UNINTERRUPTIBLE  = 2,
    THREAD_ZOMBIE           = 4,
    THREAD_STOPPED          = 8,
    THREAD_SWAPPING         = 16,
    THREAD_EXCLUSIVE        = 32,
    THREAD_CREATED          = 64,
    THREAD_LOADING          = 128
};

typedef uint64 pid_t;

#define LIFECYCLE_DEFAULT 0x0
#define LIFECYCLE_ENDED   0x1

struct threadDescriptor {
    char name[0x100];
    pid_t pid;
    listnode_t *listIdx;
    uint32 state;
    uint32 lifeCycle;
    void *pdpt;
    struct cpuState context;
} __packed;

void init_threads(void);
void generateThread_fromRoutine(void *function, char const *name);
void generateThread(char *file);
void threadListDump(void);
void cpuContextDump(struct cpuState *);
void threadDump(struct threadDescriptor *);

pid_t new_pid(void);

void contextSwitch(struct cpuState *new);
struct cpuState *getCpuContext(void);

void user_contextSwitch(struct cpuState *);
void kernel_contextSwitch(struct cpuState *);

#endif