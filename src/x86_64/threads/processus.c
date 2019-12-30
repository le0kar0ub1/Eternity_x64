#include "processus.h"
// #include "timer.h"


pid new_pid(void)
{
    static pid pid = 0x0;
    pid += 0x1;
    return (pid);
}

void init_process(void)
{

}