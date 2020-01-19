#ifndef _RSDT_H_
#define _RSDT_H_

#include "typedef.h"
#include "acpi.h"

struct rsdt {
    struct acpi_header header;
    /* table declare with [1] to point self but contain more than 1 index */
    uint32 tables[1];
} __packed;

struct xsdt {
    struct acpi_header header;
    /* table declare with [1] to point self but contain more than 1 index */
    physaddr_t tables[1];
} __packed;

#endif