#ifndef _TTY_H_
#define _TTY_H_

#include "eternity.h"
#include "commandPrototypes.h"

#define PROMPT    "[Eternity_x64]$ "
#define PROMPTLEN ((uint)strlen(PROMPT))

void fire_cmd_line(char *);

#endif
