#ifndef _SMP_H_
#define _SMP_H_

#include "eternity.h"

struct mp
{
    uchar const signature[4];   /* _MP_ */
    physaddr const conf_physaddr; /* Physaddr of the MP config table */
    uchar const length; /* Length of the table/16. Should be 1 */
    uchar const spec_rev;   /* Revision of the MP spec */
    uchar const checksum;   /* All bytes must add up to 0 */
    uchar const type;   /* MP system config type */
    uchar const imcrp;  /* IMCRP */
    uchar const reserved[3];    /* Reserved. Should be 0 */
} __packed;

struct mp_conf
{
    uchar const signature[4];   /* PCMP */
    ushort const length;    /* Table length */
    uchar const spec_rev;   /* Revision of the MP spec */
    uchar const checksum;   /* All bytes must add up to 0 */
    uchar const oem_id[8];  /* String that identifies manufacturer */
    uchar const product_id[12]; /* String that identifies product family */
    physaddr const oemtable;  /* Pointer to oem-defined conf table, or 0 */
    ushort const oemlength; /* Length of oem-defined conf table */
    ushort const entry_count;   /* Number of entries */
    physaddr const lapic_paddr;   /* Physical address of local APIC */
    ushort const xlength;   /* Extended table length */
    uchar const xchecksum;  /* All bytes of the xtable must add up to 0*/
    uchar const reserved;   /* Reserved. Should be 0 */
} __packed;

struct mp_proc
{
    uchar const type;   /* Entry Type (0) */
    uchar const lapic_id;   /* Local APIC ID */
    uchar const lapic_version;  /* Local APIC version number */
    uchar const flags;  /* CPU flags */
    uchar const signature[4];   /* CPU signature */
    uint const feature; /* CPU features */
    uchar const reserved[8];    /* Reserved */
} __packed;

struct mp_bus
{
    uchar const type;   /* Entry type (1) */
    uchar const id; /* Bus Id */
    uchar const signature[6];   /* String that identifies the bus type */
} __packed;

struct mp_ioapic
{
    uchar const type;   /* Entry type (2) */
    uchar const id; /* I/O APIC Id */
    uchar const version;    /* I/O APIC Version number */
    uchar const flags;  /* I/O APIC Flags */
    physaddr const addr;  /* I/O APIC address */
} __packed;

struct mp_ioint
{
    uchar const type;   /* Entry type (3) */
    uchar const int_type;   /* Interrupt type */
    ushort const flags; /* I/O Interrupt Flags */
    uchar const bus_id; /* Source Bus ID */
    uchar const bus_irq;    /* Source Bus IRQ */
    uchar const apic_id;    /* Destination APIC ID */
    uchar const apic_int;   /* Destination APIC int number */
} __packed;

struct mp_lint
{
    uchar const type;   /* Entry type (3) */
    uchar const int_type;   /* Interrupt type */
    ushort const flags; /* Local Interrupt Flags */
    uchar const bus_id; /* Source Bus ID */
    uchar const bus_irq;    /* Source Bus IRQ */
    uchar const apic_id;    /* Destination Local APIC ID */
    uchar const apic_int;   /* Destination Local APIC lint number */
} __packed;

enum MP_ENTRY_TYPE
{
    MP_PROCESSOR    = 0x0,
    MP_BUS  = 0x1,
    MP_IO_APIC  = 0x2,
    MP_IO_INTERRUPT = 0x3,
    MP_LOCAL_INTERRUPT  = 0x4,
};

bool    mp_init(void);
void    mp_start_aps(void);

#endif
