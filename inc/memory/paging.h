#ifndef _PAGING_H_
#define _PAGING_H_

#include "memory.h"

#define PAGE_SIZE  0x1000
#define PAGE_ENTRY 0x200

#define DPL0 0x0
#define DPL1 0x1
#define DPL2 0x2
#define DPL3 0x3

/* STANDART PAGE x86_64 (lower pagination level)*/
struct __PAGE__
{
    // union
    // {
    //     struct
    //     {
            uint64 Present : 1;              // Must be 1, region invalid if 0.
            uint64 ReadWrite : 1;            // If 0, writes not allowed.
            uint64 UserSupervisor : 1;       // If 0, user-mode accesses not allowed.
            uint64 PageWriteThrough : 1;     // Determines the memory type used to access the memory.
            uint64 PageCacheDisable : 1;     // Determines the memory type used to access the memory.
            uint64 Accessed : 1;             // If 0, this entry has not been used for translation.
            uint64 Dirty : 1;                // If 0, the memory backing this page has not been written to.
            uint64 PageAccessType : 1;       // Determines the memory type used to access the memory.
            uint64 Global: 1;                // If 1 and the PGE bit of CR4 is set, translations are global.
            uint64 Ignored2 : 3;
            uint64 PageFrameNumber : 40;     // The page frame number of the backing physical page.
            uint64 Reserved : 11;
            uint64 ExecuteDisable : 1;       // If 1, instruction fetches not allowed.
    //     };
    //    uint64 value;
    // };
};

/* STANDART PAGE LEVEL 2 3 4 */
struct __PAGE_INDEX__
{
    // union
    // {
    //     struct
    //     {
            uint64 Present : 1;              // Must be 1, region invalid if 0.
            uint64 ReadWrite : 1;            // If 0, writes not allowed.
            uint64 UserSupervisor : 1;       // If 0, user-mode accesses not allowed.
            uint64 PageWriteThrough : 1;     // Determines the memory type used to access PDPT.
            uint64 PageCacheDisable : 1;     // Determines the memory type used to access PDPT.
            uint64 Accessed : 1;             // If 0, this entry has not been used for translation.
            uint64 Ignored1 : 1;
            uint64 PageSize : 1;             // Must be 0 for PML4E.
            uint64 Ignored2 : 4;
            uint64 PageFrameNumber : 36;     // The page frame number of the PDPT of this PML4E.
            uint64 Reserved : 4;
            uint64 Ignored3 : 11;
            uint64 ExecuteDisable : 1;       // If 1, instruction fetches not allowed.
    //     };
    //     uint64 value;
    // };
};

/* LEVEL PAGINATION STRUCT*/
/* PAGE TABLE LVL 1 */
typedef struct _PT_
{
    struct __PAGE__ page[PAGE_ENTRY];
} PT;

/* PAGE DIRECTORY LVL 2 */
typedef struct _PD_
{
    struct __PAGE_INDEX__ page[PAGE_ENTRY];
} PD;

/* PAGE DIRECTORY POINTER LVL 3 */
typedef struct _PDP_
{
    struct __PAGE_INDEX__ page[PAGE_ENTRY];
} PDP;

/* PAGINATION MAX LEVEL LVL 4 */
typedef struct _PML4_
{
    struct __PAGE_INDEX__ page[PAGE_ENTRY];
} PML4;

/* Tests if x % PAGE_SIZE == 0 */
#define IS_PAGE_ALIGNED(x) (!((uintptr)(x) & (PAGE_SIZE - 1)))

/* Align the given number to the greatest-or-equal given power of 2 */
#define ALIGN(x, y) (((x) + ((y) - 1)) & ~((y) - 1))

/* Align number to PAGE_SIZE */
#define PAGE_ALIGN(x) (ALIGN(x, PAGE_SIZE))

#endif
