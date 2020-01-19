#include "memory.h"
#include "multiboot.h"

// https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html
// https://os.phil-opp.com/allocating-frames

struct multiboot_info multiboot;

struct multiboot_info *get_multiboot_struct(void)
{
    return (&multiboot);
}

/* get information give by the bootloader */
void get_multiboot_tag(uintptr addr)
{
    /* skip the 8 bytes header useless */
    struct multiboot_tag *tag = (struct multiboot_tag *) (addr + 0x8);

    if (addr & 0x7) {
        kprint("Unaligned address multiboot header : %x\n", addr);
        return;
    }
    while (tag->type != MULTIBOOT_TAG_TYPE_END) {
        switch (tag->type) {
        case MULTIBOOT_TAG_TYPE_CMDLINE:
            multiboot.cmd_line = ((struct multiboot_tag_string *) tag)->string;
            break;
        case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME: /* Loader Name */
            multiboot.bootloader = ((struct multiboot_tag_string *) tag)->string;
            break;
        case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO: /* memory used */
            multiboot.mem_lower = ((struct multiboot_tag_basic_meminfo *) tag)->mem_lower;
            multiboot.mem_upper = ((struct multiboot_tag_basic_meminfo *) tag)->mem_upper;
            break;
        case MULTIBOOT_TAG_TYPE_MMAP: /* memory is map */
            multiboot.mmap_start = (struct multiboot_memory_map_t *)((struct multiboot_tag_mmap const *)tag)->entries;
            multiboot.mmap_end = (struct multiboot_memory_map_t *)(struct multiboot_mmap_entry const *)((uchar const *)tag + tag->size);
            multiboot.mmap_entry_size = ((struct multiboot_tag_mmap const *)tag)->entry_size;
            break;
        case MULTIBOOT_TAG_TYPE_MODULE: /* no modules loaded */
            /* use it to load data at entry (later) */
            kprint("Module at %x to %x. Command line %s\n",
            ((struct multiboot_tag_module *) tag)->mod_start,
            ((struct multiboot_tag_module *) tag)->mod_end,
            ((struct multiboot_tag_module *) tag)->cmdline);
            break;
        case MULTIBOOT_TAG_TYPE_ACPI_OLD:
            break;
        case MULTIBOOT_TAG_TYPE_ACPI_NEW:
            break;
        }
        /* next tag */
        tag = (struct multiboot_tag *) ((uchar const *)tag + ((tag->size + 7) & ~7));
    }
}
