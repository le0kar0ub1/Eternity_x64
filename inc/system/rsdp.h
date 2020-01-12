#ifndef _RSDP_H_
#define _RSDP_H_

#include "typedef.h"

#define RSDP_SEARCH_START       0xE0000
#define RSDP_SEARCH_END         0xFFFFF
#define RSDP_SIGNATURE_BOUNDARY 0x10
#define RSDP_SIGNATURE          "RSD PTR "

#define RSDP_REVISION_V1 0x0
#define RSDP_REVISION_V2 0x2

#define RSDP_CHECKSUM_VALID 0x0

struct rsdp {
    char   signature[8];
    uint8  checksum;
    char   oemid[6];
    uint8  revision;
    uint32 rsdt_address
    /* IF IS V2 */;
    uint32 length;
    uint64 xsdt_address;
    uint8  ext_checksum;
    uint8  reserved[3];
} __packed;

struct rsdp *get_rsdp(void);
uint8 rsdp_checksum_isvalid(uint8 *check, size_t sz);

#endif