#ifndef _MULTIBOOT_H_
#define _MULTIBOOT_H_

#include "multiboot2.h"
#include "typedef.h"

struct multiboot_info
{
    char const *cmd_line;
    char const *bootloader;
    uintptr mem_lower;
    uintptr mem_upper;
    struct multiboot_memory_map_t const *mmap_start;
    struct multiboot_memory_map_t const *mmap_end;
    size_t mmap_entry_size;
};

#endif