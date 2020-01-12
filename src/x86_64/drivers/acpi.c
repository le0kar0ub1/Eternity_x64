#include "eternity.h"
#include "rsdp.h"

struct rsdp *rsdp = NULL; 

void init_acpi(void)
{
    rsdp = get_rsdp();
    fatalAssert(rsdp);
}