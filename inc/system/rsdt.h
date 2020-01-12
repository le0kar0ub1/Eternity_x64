#ifndef _RSDT_H_
#define _RSDT_H_

#include "typedef.h"

struct rsdt {
    struct acpi_header header;
    uint32 tables[];
} __packed;

struct xsdt {
    struct acpi_header header;
    physaddr_t tables[];
} __packed;

#endif