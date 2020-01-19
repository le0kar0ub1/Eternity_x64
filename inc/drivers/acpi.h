#ifndef _ACPI_H_
#define _ACPI_H_

#include "typedef.h"

#define SIGNATURE_MADT  0x43495041  // "APIC"
#define SIGNATURE_BOOT  0x544f4f42  // "BOOT"
#define SIGNATURE_FADT  0x50434146  // "FACP"
#define SIGNATURE_HPET  0x54455048  // "HPET"
#define SIGNATURE_MCFG  0x4746434d  // "MCFG"
#define SIGNATURE_SRAT  0x54415253  // "SRAT"
#define SIGNATURE_SSDT  0x54445353  // "SSDT"
#define SIGNATURE_WAET  0x54454157  // "WAET"

struct acpi_header {
    union
    {
        char    id[4];
        uint32  value;
    } signature;
    uint32 length;
    uint8 revision;
    uint8 checksum;
    char oem_id[6];
    char oem_table_id[8];
    uint32 oem_revision;
    uint8 creator_id[4];
    uint32 creator_revision;
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
    uint16 flags;
} __packed;

#define MADT_NMI 4
struct madt_entry_nmi {
    struct madt_entry_header header;
    uint8 acpi_id;
    uint16 flags;
    uint8 lint_num;
} __packed;

#define MADT_LAPIC_ADDR 5
struct madt_entry_lapic_addr {
    struct madt_entry_header header;
    uint16 __zero;
    uint64 lapic_addr;
} __packed;

struct acpi_fadt
{
    struct acpi_header hdr;

    uint32 firmware_ctl;  ///< Pointer to FACS firmware control block
    uint32 ptr_dsdt;      ///< Pointer to DSDT block
    uint8  reserved1;     ///< Not used
    uint8  pm_profile;    ///< Preferred power management profile
    uint16 sci_interrupt; ///< SCI interrupt vector
    uint32 smi_cmdport;   ///< SMI command port
    uint8  acpi_enable;   ///< SMI command to disable SMI ownership
    uint8  acpi_disable;  ///< SMI command to re-enable SMI ownership
    uint8  s4bios_req;    ///< SMI command to enter S4BIOS state
    uint8  pstate_ctl;    ///< SMI command to assume perf state ctl
    uint32 pm1a_evtblock; ///< Port of PM1a event register block
    uint32 pm1b_evtblock; ///< Port of PM1b event register block
    uint32 pm1a_ctlblock; ///< Port of PM1a ctl register block
    uint32 pm1b_ctlblock; ///< Port of PM1b ctl register block
    uint32 pm2_ctlblock;  ///< Port of PM2 ctl register block
    uint32 pmt_ctlblock;  ///< Port of PM timer ctl register block
    uint32 gpe0_block;    ///< Port of general-purpose event 0 reg block
    uint32 gpe1_block;    ///< Port of general-purpose event 0 reg block
    uint8  pm1_evt_len;   ///< Bytes decoded by pm1*_evtblock
    uint8  pm1_ctl_len;   ///< Bytes decoded by pm1*_ctlblock
    uint8  pm2_ctl_len;   ///< Bytes decoded by pm2_ctlblock
    uint8  pmt_ctl_len;   ///< Bytes decoded by pmt_ctlblock
    uint8  gpe0_len;      ///< Bytes decoded by gpe0_block
    uint8  gpe1_len;      ///< Bytes decoded by gpe1_block
    uint8  gpe1_base;     ///< Offset where gpe1 events start
    uint8  cstate_ctl;    ///< SMI command for C state notifications
    uint16 latency_c2;    ///< Worst-case us latency to enter C2 state
    uint16 latency_c3;    ///< Worst-case us latency to enter C3 state
    uint16 flush_size;    ///< Cache reads to flush dirty cache
    uint16 flush_stride;  ///< Cache width (flush stride)
    uint8  duty_offset;   ///< Index of P_CNT reg duty cycle setting
    uint8  duty_width;    ///< Width of P_CNT reg duty cycle setting
    uint8  alarm_day;     ///< RTC RAM index day-of-month alarm: day
    uint8  alarm_month;   ///< RTC RAM index day-of-month alarm: month
    uint8  century;       ///< RTC RAM index of century
    uint16 boot_arch;     ///< Boot architecture flags (ACPI 2.0+)
    uint8  reserved2;     ///< Not used
    uint32 flags;         ///< Fixed feature flags
} __packed;

struct acpi_mcfg
{
    struct acpi_header hdr;

    uint64 reserved;
} __packed;

struct acpi_mcfg_addr
{
    uint64 base;          ///< Base address of configuration mechanism
    uint16 seg_group;     ///< PCI segment group number
    uint8  bus_start;     ///< Start PCI bus number
    uint8  bus_end;       ///< End PCI bus number
    uint32 reserved;
} __packed;

struct acpi_madt
{
    struct acpi_header hdr;

    uint32 ptr_local_apic;   ///< Local APIC address
    uint32 flags;            ///< APIC flags
} __packed;

#endif