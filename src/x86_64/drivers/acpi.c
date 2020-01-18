#include "eternity.h"
#include "rsdp.h"
#include "memory.h"
#include "rsdt.h"
#include "paging.h"
#include "acpi.h"

struct rsdp *acpi_rsdp = NULL; 

extern pml4_t *kpml4;

void acpi_map_table(struct acpi_header *header)
{
    // kprint("%x %x\n", (uint64)header, V2P((uint64)header));
    // while (1);
    mmap_segment(kpml4, (virtaddr_t)header, (virtaddr_t)header + sizeof(struct acpi_header),
    (uintptr)V2P((uintptr)header), PRESENT | WRITABLE | USER_ACCESSIBLE | GLOBAL_PAGE);
}

bool acpi_checksum(struct acpi_header *header)
{
    uchar sum = 0;
 
    for (uint i = 0; i < header->length; i++)
        sum += ((char *)header)[i];
    return (sum == 0);
}

/*
** we have got the good idea to load the kernel really high in memory 
** and now all the system physical ptr can't be accessed directly
*/
virtaddr_t acpi_premap(physaddr_t phys, int size)
{
    virtaddr_t mapped = physical_mmap(kpml4, phys, size, PRESENT | WRITABLE | GLOBAL_PAGE);
    kprint("%x\n", mapped);
    kprint("%x %x\n", phys, virtToPhys(kpml4, mapped) << 12);
    while (1);
    memset(mapped, 0x0, 0x2);
    fatalAssert(mapped);
    return (mapped);
}

void acpi_get_table(void)
{
    if (acpi_rsdp->revision == RSDP_REVISION_V1) {
        acpi_premap(acpi_rsdp->rsdt_address, sizeof(struct rsdt));
        while(1);
        // struct rsdt *rsdt = (struct rsdt *)P2V(acpi_rsdp->rsdt_address);
        // acpi_map_table(&(rsdt->header));
    } else if (acpi_rsdp->revision == RSDP_REVISION_V2) {
        struct xsdt *xsdt = (struct xsdt *)P2V(acpi_rsdp->xsdt_address);
        acpi_map_table(&(xsdt->header));
    } else {
        PANIC("Invalid apic table\n");
    }
    
}

void init_acpi(void)
{
    acpi_rsdp = get_rsdp();
    fatalAssert(acpi_rsdp);
    acpi_get_table();
}