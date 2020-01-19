#include "eternity.h"
#include "rsdp.h"

/* is valid if equal to 0 while adding all the table byte */
uint8 rsdp_checksum_isvalid(uint8 *check, size_t sz)
{
    uint8 sum = 0x0;

    for (size_t s = 0x0; s < sz; s++)
        sum += check[s];
    return (sum);
}

struct rsdp *get_rsdp(void)
{
    /*
    ** we have identity mapped LOAD_VIRT_ADDR -> 0x0 
    ** then we can access these address with a simple P2V
    */
    virtaddr_t virt = (virtaddr_t)P2V(RSDP_SEARCH_START);
    virtaddr_t end = (virtaddr_t)P2V(RSDP_SEARCH_END);

    for (; virt < end; virt += RSDP_SIGNATURE_BOUNDARY) {
        if (memcmp((void *)virt, (void *)RSDP_SIGNATURE, 0x8)) {
            switch (*((uint8 *)virt + 15)) {
                case RSDP_REVISION_V1:
                    if (!rsdp_checksum_isvalid(virt, sizeof(struct rsdp) - 0x10))
                        return ((struct rsdp *)virt);
                    break;
                case RSDP_REVISION_V2:
                    if (!rsdp_checksum_isvalid(virt, sizeof(struct rsdp)))
                        return ((struct rsdp *)virt);
                    break;
                default:
                    break;
            }
        }
    }
    return (NULL);
}