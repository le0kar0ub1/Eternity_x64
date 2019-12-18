ENTRY(_start)
OUTPUT_FORMAT(elf64-x86-64)
OUTPUT(eternity-x86_64.bin)

__KERNEL_VIRT_BASE = 0xFFFFFFFF80000000;
__KERNEL_VIRT_LINK = 0xFFFFFFFF80100000;
__KERNEL_PHYS_START = __KERNEL_VIRT_LINK - __KERNEL_VIRT_BASE;

SECTIONS {
    . = __KERNEL_VIRT_LINK;

    .text : AT(ADDR(.text) - __KERNEL_VIRT_BASE) {
        *(.multiboot)
        *(.text .text.*)
    }

    .init_array : AT(ADDR(.init_array) - __KERNEL_VIRT_BASE) {
        start_ctors = .;
        KEEP(*( .init_array ));
        KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
        end_ctors = .;
    }

    .fini_array : AT(ADDR(.fini_array) - __KERNEL_VIRT_BASE) {
        KEEP(*( .fini_array ));
        KEEP(*(SORT_BY_INIT_PRIORITY( .fini_array.* )));
    }

    .data : AT(ADDR(.data) - __KERNEL_VIRT_BASE) {
        *(.data .data.*)
    }

    .rodata : AT(ADDR(.rodata) - __KERNEL_VIRT_BASE) {
        *(.rodata .rodata.*)
    }

    .bss : AT(ADDR(.bss) - __KERNEL_VIRT_BASE) {
        *(.bss .bss.*)
    }

    . = ALIGN(0x1000);

    __KERNEL_VIRT_END = .;
    __KERNEL_PHYS_SIZE = __KERNEL_PHYS_END - __KERNEL_PHYS_START;
    __KERNEL_VIRT_SIZE = __KERNEL_VIRT_END - __KERNEL_VIRT_LINK;
    __KERNEL_PHYS_END = . - __KERNEL_VIRT_BASE;
}
