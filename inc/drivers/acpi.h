#ifndef _ACPI_H_
#define _ACPI_H_

#include "typedef.h"

#define SIGNATURE_MADT      0x43495041           // "APIC"
#define SIGNATURE_BOOT      0x544f4f42           // "BOOT"
#define SIGNATURE_FADT      0x50434146           // "FACP"
#define SIGNATURE_HPET      0x54455048           // "HPET"
#define SIGNATURE_MCFG      0x4746434d           // "MCFG"
#define SIGNATURE_SRAT      0x54415253           // "SRAT"
#define SIGNATURE_SSDT      0x54445353           // "SSDT"
#define SIGNATURE_WAET      0x54454157           // "WAET"

struct acpi_header {
    char signature[4];
    uint32 length;
    uint8 revision;
    uint8 checksum;
    char oem_id[6];
    char oem_table_id[8];
    uint32 oem_revision;
    uint8 creator_id[4];
    uint32 creator_revision;
} __packed;

struct acpi_madt {
    struct acpi_header header;
    uint32 lapic_address;
    uint32 flags;
    uint8  *entries; // is on the entries
} __packed;

struct madt_entry_header {
    uint8 type;
    uint8 length;
} __packed;

#define MADT_LAPIC 0
struct madt_entry_lapic {
    struct madt_entry_header header;
    uint8 acpi_id;
    uint8 apic_id;
    uint32 flags;
} __packed;

#define MADT_IOAPIC 1
struct madt_entry_ioapic {
    struct madt_entry_header header;
    uint8 apic_id;
    uint8 __zero;
    uint32 phys_addr;
    uint32 gsi_base;
} __packed;

#define MADT_OVERRIDE 2
struct madt_entry_override {
    struct madt_entry_header header;
    uint8 bus; // Constant, set to 0
    uint8 source;
    uint32 gsi;
    uint16_t flags;
} __packed;

#define MADT_NMI 4
struct madt_entry_nmi {
    struct madt_entry_header header;
    uint8 acpi_id;
    uint16_t flags;
    uint8 lint_num;
} __packed;

#define MADT_LAPIC_ADDR 5
struct madt_entry_lapic_addr {
    struct madt_entry_header header;
    uint16_t __zero;
    uint64_t lapic_addr;
} __packed;

#endif