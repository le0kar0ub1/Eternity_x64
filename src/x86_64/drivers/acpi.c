#include "eternity.h"
#include "rsdp.h"

struct rsdp *acpi_rsdp = NULL; 

void init_acpi(void)
{
    acpi_rsdp = get_rsdp();
    fatalAssert(acpi_rsdp);
}