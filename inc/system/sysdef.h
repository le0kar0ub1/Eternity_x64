#ifndef _SYSDEF_H_
#define _SYSDEF_H_

#include "typedef.h"

#define MAX_ADDR_32B_SYS 0xFFFFFFFF
#define MAX_ADDR_64B_SYS 0xFFFFFFFFFFFFFFFF

extern uint64 __KERNEL_VIRT_BASE;
extern uint64 __KERNEL_VIRT_LINK;
extern uint64 __KERNEL_VIRT_END;
extern uint64 __KERNEL_PHYS_START;
extern uint64 __KERNEL_PHYS_END;

#define LOAD_PHYS_ADDR      ((uint64)&__KERNEL_PHYS_START)
#define LOAD_VIRT_ADDR      (&__KERNEL_VIRT_LINK)
#define KERN_VIRT_BASE      (&__KERNEL_VIRT_BASE)
#define PHYS_MM_START_USED  (ALIGN_PAGE((uint64)&__KERNEL_PHYS_END))

#endif
