# Eternity is a x86_64 kernel

**Eternity is writing (with love) in C and x86 assembly.**

## DEPENDENCY:

    - _qemu_ / _qemu-kvm_ (Virtualisation)
    - _grub-mkrescue_ and _libisoburn_
    - _make_
    - _nasm_
    - _gcc_ for x86_64-elf target

## BUILD:

    - make

## RUN:

    - make run
_Eternity is running with KVM module, if this can't be set on your computer delete the flags "-enable-kvm" in (quemuflags) Makefile._

## INTERACTION:

    - TTY (azerty keyboard only)
    - Command line ("help" in to see available commands)

## ROADMAP:

- [X] Kernel loaded higher-half
- [X] Boot
  - [X] Multiboot 2
  - [X] Paging setup
  - [X] GDT setup
  - [X] IDT setup
  - [X] TSS setup
  - [ ] SMP setup (will be implemented ?)
- [X] Basic drivers
  - [X] VGA
  - [X] PS/2 Keyboard
  - [ ] PS/2 Mouse
  - [X] RTC
  - [X] Timer
- [ ] Memory
  - [X] Physical Memory Management
  - [X] Virtual Memory Management
  - [ ] Memory Abstractor
  - [X] Kernel heap
- [ ] ELF Loader
- [X] Syscall interface and userspace (ring 3)
- [ ] Multi process / threads
  - [ ] Basic Scheduling
  - [X] User Threads
  - [X] Kernel threads
  - [ ] Processes
- [ ] Initrd
- [ ] Filesystem

## EPILOGUE

_Eternity is in development._

sure you want the QEMU technical documentation: https://qemu.weilnetz.de/doc/qemu-doc.html
