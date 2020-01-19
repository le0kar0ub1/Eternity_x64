#include "eternity.h"
#include "rsdp.h"
#include "memory.h"
#include "rsdt.h"
#include "paging.h"
#include "acpi.h"

struct rsdp *acpi_rsdp = NULL; 

struct acpi_fadt *acpi_fadt;
struct acpi_madt *acpi_madt;
struct acpi_mcfg *acpi_mcfg;

extern pml4_t *kpml4;

void acpi_map_table(struct acpi_header *header, physaddr_t phys)
{
    mmap_segment(kpml4, (virtaddr_t)header, (virtaddr_t)header + header->length,
    phys, PRESENT | WRITABLE | USER_ACCESSIBLE | GLOBAL_PAGE);
}

bool acpi_checksum(struct acpi_header *header)
{
    uchar sum = 0;
 
    for (uint i = 0; i < header->length; i++)
        sum += ((char *)header)[i];
    return (sum == 0);
}

/*
** We have got the good idea to load the kernel really high in memory 
** and now all the system ptr can't be accessed directly
** then, we must map ptr by ptr to access them
*/
virtaddr_t acpi_premap(physaddr_t phys, int size)
{
    virtaddr_t mapped = physical_mmap(kpml4, phys, size, PRESENT | WRITABLE | GLOBAL_PAGE);
    fatalAssert(mapped);
    return (mapped);
}

void acpi_print_table(struct acpi_header *hd)
{
    kprint("%c%c%c%c at %x, OEM %c%c%c%c%c%c\n",
         hd->signature.id[0], hd->signature.id[1], hd->signature.id[2], hd->signature.id[3], (uint64)virtToPhys(kpml4, (virtaddr_t)hd),
         hd->oem_id[0], hd->oem_id[1], hd->oem_id[2], hd->oem_id[3], hd->oem_id[4], hd->oem_id[5]);
    kprint("Length: %d\n", hd->length);
    kprint("Revision: %d\n", hd->revision);
    kprint("OEM Table ID: %c%c%c%c%c%c%c%c\n", hd->oem_table_id[0], hd->oem_table_id[1], hd->oem_table_id[2],
         hd->oem_table_id[3], hd->oem_table_id[4], hd->oem_table_id[5], hd->oem_table_id[6], hd->oem_table_id[7]);
    kprint("OEM Revision: %d\n", hd->oem_revision);
    kprint("Creator ID: %c%c%c%c\n", hd->creator_id[0], hd->creator_id[1], hd->creator_id[2], hd->creator_id[3]);
    kprint("Creator Revision: %d\n\n", hd->creator_revision);
}

void acpi_read_table(struct acpi_header *head)
{
    switch (head->signature.value) {
        case SIGNATURE_FADT:
            acpi_fadt = (struct acpi_fadt *)head;
            break;
        case SIGNATURE_MADT:
            acpi_madt = (struct acpi_madt *)head;
            break;
        case SIGNATURE_MCFG:
            acpi_mcfg = (struct acpi_mcfg *)head;
            break;
        default:
            verbose_log("Unknow acpi signature\n");
            break;
    }
}

void acpi_get_table(void)
{
    if (acpi_rsdp->revision == RSDP_REVISION_V1) {
        struct rsdt *virtrsdt = acpi_premap(acpi_rsdp->rsdt_address, sizeof(struct rsdt));
        acpi_map_table(&virtrsdt->header, (physaddr_t)acpi_rsdp->rsdt_address);
        if (!acpi_checksum(&virtrsdt->header))
            PANIC("ACPI checksum failed");
        uint32 entries = ((virtrsdt->header.length) - sizeof(struct acpi_header)) / 0x4;
        for (uint inc = 0x0; inc < entries; inc++) {
            uintptr physHdr = (uintptr)virtrsdt->tables[inc];
            struct acpi_header *virtHdr = acpi_premap(physHdr, 0x80);
            acpi_print_table(virtHdr);
            acpi_read_table(virtHdr);
            serial_kprint("phys table[%d] = %x %x\n", inc, (uint64)physHdr, (uint64)virtHdr);
        }
    } else if (acpi_rsdp->revision == RSDP_REVISION_V2) {
        struct rsdt *xsdtvirt = acpi_premap(acpi_rsdp->xsdt_address, sizeof(struct rsdt));
        acpi_map_table(&xsdtvirt->header, (physaddr_t)acpi_rsdp->xsdt_address);
    } else {
        PANIC("APIC Invalid table");
    }
    while(1);
}

void init_acpi(void)
{
    acpi_rsdp = get_rsdp();
    fatalAssert(acpi_rsdp);
    acpi_get_table();
}