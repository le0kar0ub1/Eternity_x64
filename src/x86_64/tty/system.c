#include "eternity.h"

void uname(void)
{
    kprint("Eternity_x64 release 1.0\n");
}

void help(void)
{
    extern char const *ttyCmdDef[];
    kprint("Available commands:\n");
    for (uint i = 0x0; ttyCmdDef[i]; i++)
        kprint("    %s\n", ttyCmdDef[i]);
}
