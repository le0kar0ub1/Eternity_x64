#include "eternity.h"
#include "virtualSegment.h"
#include "virtualAddressSpace.h"
#include "threads.h"
#include "descriptors.h"
#include "paging.h"

void init_tty(void);
void fire_userspace(void);
void userspace(void);

void yo(void)
{
    while (1);
    kprint("thread yooooooo\n");
    // exit(0);
}

void kmain(void)
{
    // init_tty();
    // fire_userspace();
    struct vseg *seg = vseg_init((pml4_t *)get_current_pml4(), (virtaddr_t)0x10000000, (virtaddr_t)0x10001000, MMAP_DEFAULT_USER_SPACE);
    vaspace_init((pml4_t *)get_current_pml4(), read_cr3(), seg, MMAP_DEFAULT_USER_SPACE);
    dumpPageAttrib(get_current_pml4(), seg->start);
    uint64 *start = (uint64 *)seg->start;
    serial_kprint("%x %x\n", (uint64)start, virtToPhys(get_current_pml4(), seg->start));
    while (1);
    uint64 a = start[0];
    sti();
    init_threads();
    // generateThread_fromRoutine(userspace, "userspace root");
    generateThread_fromRoutine(yo, "root thread");
    sti();
    /* unreachable code bcs the root userspace thread will be fired and no return are possible */
    while (0x1);
}
