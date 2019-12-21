#include "eternity.h"
#include "kheap.h"

void kmain(void)
{
    char *str = kalloc(0x2001);
    dump_kheap();
    fromCstToWr("j'insere des bytes dans les fesses de brian\n", str);
    kprint(str);
    kfree(str);
    dump_kheap();
    hlt();
}
