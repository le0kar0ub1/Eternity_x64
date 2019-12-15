# Eternity is a x86_64 kernel

**Eternity is a kernel writing (with love) in C and assembly language.**

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
    - For the moment you can only write char on screen (azerty keyboard only)

    - char '²' change the text coloration (yes, it's useless)

## BUILT:
    - Multiboot 2 boot

## EPILOGUE:
    - project is in development

sure you want the QEMU technical documentation:
https://qemu.weilnetz.de/doc/qemu-doc.html
