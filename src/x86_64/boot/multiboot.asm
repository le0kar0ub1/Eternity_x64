%include "boot.inc"
%include "memory.inc"

bits 32

[section .multiboot]
mb_header:
    dd MAGIC_HEADER_MB2
    dd PROTECTED_MODE            ; architecture 0 (protected mode i386)
    dd mb_header_end - mb_header ; mb_header length
    ; checksum
    dd 0x100000000 - (MAGIC_HEADER_MB2 + PROTECTED_MODE + (mb_header_end - mb_header))

    dw MULTIBOOT_HEADER_TAG_END ; type
    dw 0x0                      ; flags
    dd 0x8                      ; size
mb_header_end:
