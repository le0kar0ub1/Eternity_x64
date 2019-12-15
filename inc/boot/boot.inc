%ifndef _BOOT_INC_
%define _BOOT_INC_

%include "macro.inc"

%define KERNEL_STACK_SIZE         (0x10 * 0x400)

%define MAGIC_HEADER_MB2          0xE85250D6
%define PROTECTED_MODE            0x0
%define MULTIBOOT_HEADER_TAG_END  0x0

; Should be in eax at boot
%define MAGIC_BOOTLOADER_MB2      0x36d76289

; serial port
%define PORT 0x3f8   /* COM1 */

%endif
