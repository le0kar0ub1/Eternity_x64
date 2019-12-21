#include "eternity.h"
#include "pci.h"

uint32_t pci_size_map[100];
pci_dev_t dev_zero= {0};

uint32_t pci_read(pci_dev_t dev, uint32_t field) {
    // Only most significant 6 bits of the field
    dev.field_num = (field & 0xFC) >> 2;
    dev.enable = 1;
    outportl(PCI_CONFIG_ADDRESS, dev.bits);

    // What size is this field supposed to be ?
    uint32_t size = pci_size_map[field];
    if(size == 1) {
        // Get the first byte only, since it's in little endian, it's actually the 3rd byte
        uint8_t t =inportb(PCI_CONFIG_DATA + (field & 3));
        return t;
    }
    else if(size == 2) {
        uint16_t t = inports(PCI_CONFIG_DATA + (field & 2));
        return t;
    }
    else if(size == 4){
        // Read entire 4 bytes
        uint32_t t = inportl(PCI_CONFIG_DATA);
        return t;
    }
    return 0xffff;
}

void pci_write(pci_dev_t dev, uint32_t field, uint32_t value) {
    dev.field_num = (field & 0xFC) >> 2;
    dev.enable = 1;
    // Tell where we want to write
    outportl(PCI_CONFIG_ADDRESS, dev.bits);
    // Value to write
    outportl(PCI_CONFIG_DATA, value);
}

uint32_t get_device_type(pci_dev_t dev) {
    uint32_t t = pci_read(dev, PCI_CLASS) << 8;
    return t | pci_read(dev, PCI_SUBCLASS);
}

uint32_t get_secondary_bus(pci_dev_t dev) {
    return pci_read(dev, PCI_SECONDARY_BUS);
}

uint32_t pci_reach_end(pci_dev_t dev) {
    uint32_t t = pci_read(dev, PCI_HEADER_TYPE);
    return !t;
}

pci_dev_t pci_scan_function(uint16_t vendor_id, uint16_t device_id, uint32_t bus, uint32_t device, uint32_t function, int device_type) {
    pci_dev_t dev = {0};
    dev.bus_num = bus;
    dev.device_num = device;
    dev.function_num = function;
    // If it's a PCI Bridge device, get the bus it's connected to and keep searching
    if(get_device_type(dev) == PCI_TYPE_BRIDGE) {
        pci_scan_bus(vendor_id, device_id, get_secondary_bus(dev), device_type);
    }
    // If type matches, we've found the device, just return it
    if(device_type == -1 || device_type == get_device_type(dev)) {
        uint32_t devid  = pci_read(dev, PCI_DEVICE_ID);
        uint32_t vendid = pci_read(dev, PCI_VENDOR_ID);
        if(devid == device_id && vendor_id == vendid)
        return dev;
    }
    return dev_zero;
}

pci_dev_t pci_scan_device(uint16_t vendor_id, uint16_t device_id, uint32_t bus, uint32_t device, int device_type) {
    pci_dev_t dev = {0};
    dev.bus_num = bus;
    dev.device_num = device;

    if(pci_read(dev,PCI_VENDOR_ID) == PCI_NONE)
    return dev_zero;

    pci_dev_t t = pci_scan_function(vendor_id, device_id, bus, device, 0, device_type);
    if(t.bits)
        return t;

    if(pci_reach_end(dev))
    return dev_zero;

    int function;
    for(function = 1; function < FUNCTION_PER_DEVICE; function++) {
        if(pci_read(dev,PCI_VENDOR_ID) != PCI_NONE) {
            t = pci_scan_function(vendor_id, device_id, bus, device, function, device_type);
            if(t.bits)
                return t;
        }
    }
    return dev_zero;
}

pci_dev_t pci_scan_bus(uint16_t vendor_id, uint16_t device_id, uint32_t bus, int device_type) {
    int device;
    for(device = 0; device < DEVICE_PER_BUS; device++) {
        pci_dev_t t = pci_scan_device(vendor_id, device_id, bus, device, device_type);
        if(t.bits)
            return t;
    }
    return dev_zero;
}

pci_dev_t pci_get_device(uint16_t vendor_id, uint16_t device_id, int device_type) {

    pci_dev_t t = pci_scan_bus(vendor_id, device_id, 0, device_type);

    if(t.bits)
        return (t);

    if(pci_reach_end(dev_zero)) {
        printf("PCI Get device failed...\n");
    }
    int function;
    for (function = 1; function < FUNCTION_PER_DEVICE; function++) {
        pci_dev_t dev = {0};
        dev.function_num = function;

        if (pci_read(dev, PCI_VENDOR_ID) == PCI_NONE)
        break;
        t = pci_scan_bus(vendor_id, device_id, function, device_type);
        if (t.bits)
            return (t);
    }
    return (dev_zero);
}

void pci_init(void) {
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
