ENTRY(init)
OUTPUT_FORMAT(elf64-x86-64)
OUTPUT(eternity-x86_64.bin)

KERNEL_VIRT_BASE = 0xFFFFC00000000000;
KERNEL_VIRT_START = 0xFFFFC00000100000;
KERNEL_PHYS_START = KERNEL_VIRT_START - KERNEL_VIRT_BASE;

SECTIONS
{
    . = 4M;
    KERNEL_PHYS_START = .;

    /* .init :
    {
        build/arch/x86_64/boot/boot.o (.text)
    } */
      .boottext :
    {
      build/arch/x86_64/boot/boot.o (.multiboot)
      build/arch/x86_64/boot/boot.o (.text)
    }
  .bootrodata :
    {
      build/arch/x86_64/boot/boot.o (.rodata)
    }
  .bootdata :
    {
      build/arch/x86_64/boot/boot.o (.data)
    }
  .bootbss :
    {
      build/arch/x86_64/boot/boot.o (.bss)
      build/arch/x86_64/boot/boot.o (COMMON)
    }

  . = ALIGN(0x1000);
  _boot_end = .;

    . += KERNEL_VIRT_START;

    .text : AT(ADDR(.text) - KERNEL_VIRT_START)
    {
        __code = .;
        *(.text)
        *(.rodata*)
        . = ALIGN(0x1000);
    }

    .data : AT(ADDR(.data) - KERNEL_VIRT_START)
    {
        __data = .;
        *(.data)
        . = ALIGN(0x1000);
    }

    .rodata : AT(ADDR(.rodata) - KERNEL_VIRT_START)
    {
        __rodata = .;
        *(.rodata)
        . = ALIGN(0x1000);
    }

    .eh_frame : AT(ADDR(.eh_frame) - KERNEL_VIRT_START)
    {
        __ehframe = .;
        *(.eh_frame)
        . = ALIGN(0x1000);
    }

    .bss : AT(ADDR(.bss) - KERNEL_VIRT_START)
    {
        __bss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(0x1000);
    }

    KERNEL_VIRT_END = .;

    KERNEL_PHYS_END = (LOADADDR (.bss) + SIZEOF (.bss) + 0xFFF) & 0xFFFFFFFFFFFFF000;

    /DISCARD/ :
    {
        *(.comment)
    }
}
