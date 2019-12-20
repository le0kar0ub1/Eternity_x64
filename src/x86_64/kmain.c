#include "eternity.h"
#include "kheap.h"

void kmain(void)
{
    char *str = kalloc(0xA);
    for (uint8 i = 0x0; i < 0xA; i++)
        str[i] = i + 0x41;
    str[0x9] = 0x0;
    kprint("%x\n", str);
    kfree(str);
    char *new = kalloc(0x9);
    hlt();
    kprint("%x\n", &new);
    hlt();
}
