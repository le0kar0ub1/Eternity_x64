#ifndef _RSDT_H_
#define _RSDT_H_

#include "typedef.h"
#include "acpi.h"

struct rsdt {
    struct acpi_header header;
    uint32 *tables; // pointer is on the table
} __packed;

struct xsdt {
    struct acpi_header header;
    physaddr_t *tables; // pointer is on the table
} __packed;

#endif