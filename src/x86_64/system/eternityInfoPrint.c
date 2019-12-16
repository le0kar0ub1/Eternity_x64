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
    kprint("Mapping VMM to PMM\n");
    kprint("GDT & IDT set up and fonctionnal\n");
    kprint("Exceptions handler & default handler\n");
    kprint("Serial ports...\n");
    kprint("PIC driver....\n");
    kprint("VGA driver...\n");
    kprint("Keyboard driver...");
}
