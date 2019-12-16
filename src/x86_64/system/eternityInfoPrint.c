#include "eternity.h"

void helloFromEternity(void)
{
    char const *kernelName = "\
 _____ _____ ___________ _   _ _____ _______   __        ____    ___\n\
|  ___|_   _|  ___| ___ \\ \\ | |_   _|_   _\\ \\ / /       / ___|  /   |\n\
| |__   | | | |__ | |_/ /  \\| | | |   | |  \\ V /  __  _/ /___  / /| |\n\
|  __|  | | |  __||    /| . ` | | |   | |   \\ /   \\ \\/ / ___ \\/ /_| |\n\
| |___  | | | |___| |\\ \\| |\\  |_| |_  | |   | |    >  <| \\_/ |\\___  |\n\
\\____/  \\_/ \\____/\\_| \\_\\_| \\_/\\___/  \\_/   \\_/   /_/\\_\\_____/    |_/\n\
";
    vga_set_attrib(VGA_YELLOW, VGA_BLACK);
    vga_putstr(kernelName);
    vga_set_attrib(VGA_WHITE, VGA_BLACK);
    kprint("\nEternity_x64 project is restricted by the GNU V3 License\n\n");
    kprint("Kernel has been loaded at virtual address %x\n", KERNEL_VIRT_LINK);
    kprint("Boot sanity check...");
    kprint("Mapping VMM to PMM\n");
    kprint("Loading GDT...\n");
    kprint("jumping into long mode...\n");
    kprint("Initializing ISR...\n");
    kprint("Loading IDT...\n");
    kprint("Exceptions handler operationnal\n");
    kprint("Initializing VGA driver...");
    kprint("Initializing Serial ports...\n");
    kprint("Initializing PIC driver....\n");
    kprint("Initializing Keyboard driver...");
    kprint("Initializing PMM...\n");
}
