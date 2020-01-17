#include "threads.h"
#include "interrupt.h"
#include "timer.h"
#include "rflags.h"

extern list_t *threadList;

void threadListDump(void)
{
    listnode_t *dump = threadList->head;
    uint64 listSize = threadList->size;

    if (!dump)
        return;
    kprint("Thread list:\n");
    for (; listSize > 0x0; dump = dump->next, listSize--)
        kprint("    :: '%s'\n", ((struct threadDescriptor *)dump->item)->name);
}

void threadDump(struct threadDescriptor *thread)
{
    kprint("Thread descriptor:\n");
    kprint("    : name  : %s\n", thread->name);
    kprint("    : pid   : %l\n", thread->pid);
    kprint("    : stack : %x\n", thread->context.rsp);
    kprint("    : state : %d\n", thread->state);
    kprint("    : life  : %d\n", thread->lifeCycle);
}

void cpuContextDump(struct cpuContext *state)
{
    kprint("Processor context:\n");
    kprint("    | rax : %l | rbx : %l | rcx : %l\n", state->rax, state->rbx, state->rcx);
    kprint("    | rdx : %l | rsi : %l | rdi : %l\n", state->rdx, state->rsi, state->rdi);
    kprint("    | r8  : %l | r9  : %l | r10 : %l\n", state->r8 , state->r9, state->r10);
    kprint("    | r11 : %l | r12 : %l | r13 : %l\n", state->r11, state->r12, state->r13);
    kprint("    | r14 : %l | r15 : %l\n", state->r14, state->r15);
    kprint("    | cs  : %l | ss  : %l | ds : %l\n", state->cs , state->ss, state->ds);
    kprint("    | gs  : %l | fs  : %l | es : %l\n", state->gs, state->fs, state->es);
    kprint("    | rflags : %b\n", state->rflags);
    kprint("    | rip : %x\n", state->rip);
    kprint("    | rsp : %x | rbp : %x\n", state->rsp, state->rbp);
    kprint("    | cr3 : %x (unused)\n", state->cr3);
    // kprint("    :    xmm : %l\n", state->xmm);
}