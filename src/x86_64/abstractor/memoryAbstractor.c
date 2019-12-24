#include "eternity.h"
#include "kheap.h"
#include "vmm.h"

struct addressSpace {
    virtaddr lowKheap;
    virtaddr highKheap;
    virtaddr pml4;
};
