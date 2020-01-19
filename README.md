# Eternity is a x86_64 kernel

**Eternity is a kernel wroten (with love) in C and x86 assembly.**

## DEPENDENCY:
    - QEMU / QEMU-KVM (Virtualisation)

    - NASM

    - GCC for x86_64-elf target

## BUILD:
    - make

## RUN:
    - make run
_Eternity is running with KVM module, if this can't be set on your computer delete the flags "-enable-kvm" in (quemuflags) Makefile._

## INTERACTION:
    - TTY (azerty keyboard only)
    - Command line ("help" in to see available commands)
    - touch '²' change the text color (yes, it's useless)

## BUILT:
    - Multiboot 2 boot
    - VGA driver
    - GDT
    - IDT
    - PIC
    - 4KIB Paging
    - PMM manager
    - VMM manager
    - PCI
    - PIT
    - RTC
    - Keyboard driver
    - Threading
    - Userspace (root thread | no thread)
    - Syscall

## EPILOGUE
_Eternity is in development._

sure you want the QEMU technical documentation: https://qemu.weilnetz.de/doc/qemu-doc.html
