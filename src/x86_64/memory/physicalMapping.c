#include "paging.h"
#include "vmm.h"
#include "pmm.h"
#include "pagedef.h"
#include "ports.h"

#define VMM_PHYS_MAPPING_RESERVED_PML4_INDEX 400

extern pml4_t *kpml4;

static uint16 VMM_PHYS_MAPPING_RESERVED_PDPT_INDEX = 0x0;
static uint16 VMM_PHYS_MAPPING_RESERVED_PD_INDEX   = 0x0;
static uint16 VMM_PHYS_MAPPING_RESERVED_PT_INDEX   = 0x0;

void physicalMapping_increaseIndex(void)
{
    /* hugly */
    if (VMM_PHYS_MAPPING_RESERVED_PT_INDEX + 1 > PAGE_ENTRY_NBR - 0x1) {
        VMM_PHYS_MAPPING_RESERVED_PT_INDEX = 0x0;
        if (VMM_PHYS_MAPPING_RESERVED_PD_INDEX + 1 > PAGE_ENTRY_NBR - 0x1) {
            VMM_PHYS_MAPPING_RESERVED_PD_INDEX = 0x0;
            VMM_PHYS_MAPPING_RESERVED_PDPT_INDEX += 0x1;
        } else {
            VMM_PHYS_MAPPING_RESERVED_PD_INDEX += 0x1;
        }
    } else {
        VMM_PHYS_MAPPING_RESERVED_PT_INDEX += 0x1;
    }
}

virtaddr_t physical_mmap(pml4_t *root, physaddr_t phys, uint size, int flag)
{
    if (!IS_PAGE_ALIGNED(size))
        size = ALIGN_PAGE(size);
    uint page = (size + (phys - ROUND_DOWN(phys))) / PAGE_SIZE;

    /* align on the lower page */
    phys = ROUND_DOWN(phys);
    virtaddr_t virt = fromIndexToAdrr(VMM_PHYS_MAPPING_RESERVED_PML4_INDEX, VMM_PHYS_MAPPING_RESERVED_PDPT_INDEX,
    VMM_PHYS_MAPPING_RESERVED_PD_INDEX, VMM_PHYS_MAPPING_RESERVED_PT_INDEX);
    while (page > 0x0) {
        mmap(root, virt, phys, flag);
        physicalMapping_increaseIndex();
        phys += FRAME_SIZE;
        virt += PAGE_SIZE;
        page -= 0x1;
    }
    return (virt);
}