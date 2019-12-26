# Eternity is a x86_64 kernel

**Eternity is a kernel wrote (with love) in C and x86 assembly.**

## DEPENDENCY:
    - QEMU/QEMU-KVM (need setting Virtualisation in BIOS)

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
    - char '²' change the text coloration (yes, it's useless)

## BUILT:
    - Multiboot 2 boot
    - VGA driver
    - GDT
    - IDT
    - PIC
    - 4KIB Paging
    - PMM manager
    - VMM manager
    - PIT timer
    - RTC (Real Time Clock)
    - Keyboard driver

## EPILOGUE:
    - project is in development

sure you want the QEMU technical documentation:
https://qemu.weilnetz.de/doc/qemu-doc.html
