#include "eternity.h"
#include "pci.h"
#include "ports.h"

uint32 pci_size_map[100];
pci_dev_t dev_zero = {0};

uint32 pci_read(pci_dev_t dev, uint32 field)
{
    // Only most significant 6 bits of the field
    dev.field_num = (field & 0xFC) >> 2;
    dev.enable = 1;
    outd(PCI_CONFIG_ADDRESS, dev.bits);

    // What size is this field supposed to be ?
    uint32 size = pci_size_map[field];
    if (size == 1) {
        // Get the first byte only, since it's in little endian, it's actually the 3rd byte
        uint8 ret = inb(PCI_CONFIG_DATA + (field & 3));
        return (ret);
    } else if (size == 2) {
        uint16 ret = inw(PCI_CONFIG_DATA + (field & 2));
        return (ret);
    } else if (size == 4){
        // Read entire 4 bytes
        uint32 ret = ind(PCI_CONFIG_DATA);
        return (ret);
    }
    return (0xffff);
}

void pci_write(pci_dev_t dev, uint32 field, uint32 value)
{
    dev.field_num = (field & 0xFC) >> 2;
    dev.enable = 1;
    // Tell where we want to write
    outd(PCI_CONFIG_ADDRESS, dev.bits);
    // Value to write
    outd(PCI_CONFIG_DATA, value);
}

uint32 get_device_type(pci_dev_t dev)
{
    uint32 rd = pci_read(dev, PCI_CLASS) << 8;
    return (rd | pci_read(dev, PCI_SUBCLASS));
}

uint32 get_secondary_bus(pci_dev_t dev)
{
    return (pci_read(dev, PCI_SECONDARY_BUS));
}

uint32 pci_reach_end(pci_dev_t dev)
{
    uint32 rd = pci_read(dev, PCI_HEADER_TYPE);
    return (!rd);
}

pci_dev_t pci_scan_function(uint16 vendor_id, uint16 device_id, uint32 bus, uint32 device, uint32 function, int device_type)
{
    pci_dev_t dev = {0};
    dev.bus_num = bus;
    dev.device_num = device;
    dev.function_num = function;
    // If it's a PCI Bridge device, get the bus it's connected to and keep searching
    if (get_device_type(dev) == PCI_TYPE_BRIDGE)
        pci_scan_bus(vendor_id, device_id, get_secondary_bus(dev), device_type);
    // If type matches, we've found the device, just return it
    if (device_type == -1 || device_type == (int)get_device_type(dev)) {
        uint32 devid  = pci_read(dev, PCI_DEVICE_ID);
        uint32 vendid = pci_read(dev, PCI_VENDOR_ID);
        if (devid == device_id && vendor_id == vendid)
            return (dev);
    }
    return (dev_zero);
}

pci_dev_t pci_scan_device(uint16 vendor_id, uint16 device_id, uint32 bus, uint32 device, int device_type)
{
    pci_dev_t dev = {0};
    dev.bus_num = bus;
    dev.device_num = device;

    if (pci_read(dev,PCI_VENDOR_ID) == PCI_NONE)
        return (dev_zero);
    pci_dev_t pciDev = pci_scan_function(vendor_id, device_id, bus, device, 0, device_type);
    if (pciDev.bits)
        return (pciDev);
    if (pci_reach_end(dev))
        return (dev_zero);
    int function = 0x1;
    for (; function < FUNCTION_PER_DEVICE; function++) {
        if (pci_read(dev,PCI_VENDOR_ID) != PCI_NONE) {
            pciDev = pci_scan_function(vendor_id, device_id, bus, device, function, device_type);
            if (pciDev.bits)
                return (pciDev);
        }
    }
    return (dev_zero);
}

pci_dev_t pci_scan_bus(uint16 vendor_id, uint16 device_id, uint32 bus, int device_type)
{
    int device;
    for (device = 0; device < DEVICE_PER_BUS; device++) {
        pci_dev_t pciDev = pci_scan_device(vendor_id, device_id, bus, device, device_type);
        if (pciDev.bits)
            return (pciDev);
    }
    return (dev_zero);
}

pci_dev_t pci_get_device(uint16 vendor_id, uint16 device_id, int device_type)
{

    pci_dev_t pciDev = pci_scan_bus(vendor_id, device_id, 0, device_type);

    if (pciDev.bits)
        return (pciDev);
    if (pci_reach_end(dev_zero))
        kprint("PCI Get device failed...\n");
    int function = 0x1;
    for (; function < FUNCTION_PER_DEVICE; function++) {
        pci_dev_t dev = {0};
        dev.function_num = function;
        if (pci_read(dev, PCI_VENDOR_ID) == PCI_NONE)
            break;
        pciDev = pci_scan_bus(vendor_id, device_id, function, device_type);
        if (pciDev.bits)
            return (pciDev);
    }
    return (dev_zero);
}

void init_pci(void)
{
    pci_size_map[PCI_VENDOR_ID]       = 0x2;
    pci_size_map[PCI_DEVICE_ID]       = 0x2;
    pci_size_map[PCI_COMMAND]         = 0x2;
    pci_size_map[PCI_STATUS]          = 0x2;
    pci_size_map[PCI_SUBCLASS]        = 0x1;
    pci_size_map[PCI_CLASS]           = 0x1;
    pci_size_map[PCI_CACHE_LINE_SIZE] = 0x1;
    pci_size_map[PCI_LATENCY_TIMER]   = 0x1;
    pci_size_map[PCI_HEADER_TYPE]     = 0x1;
    pci_size_map[PCI_BIST]            = 0x1;
    pci_size_map[PCI_BAR0]            = 0x4;
    pci_size_map[PCI_BAR1]            = 0x4;
    pci_size_map[PCI_BAR2]            = 0x4;
    pci_size_map[PCI_BAR3]            = 0x4;
    pci_size_map[PCI_BAR4]            = 0x4;
    pci_size_map[PCI_BAR5]            = 0x4;
    pci_size_map[PCI_INTERRUPT_LINE]  = 0x1;
    pci_size_map[PCI_SECONDARY_BUS]   = 0x1;
}
