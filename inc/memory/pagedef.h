#ifndef _PAGEDEF_H_
#define _PAGEDEF_H_

#include "typedef.h"

typedef struct __pml4_entry__
{
    uint64 present : 1;              // Must be 1, region invalid if 0.
    uint64 rw : 1;            // If 0, writes not allowed.
    uint64 supervisor : 1;       // If 0, user-mode accesses not allowed.
    uint64 PageWriteThrough : 1;     // Determines the memory type used to access PT.
    uint64 PageCacheDisable : 1;     // Determines the memory type used to access PT.
    uint64 Accessed : 1;             // If 0, this entry has not been used for translation.
    uint64 dirty : 1;
    uint64 pagesize : 1;             // If 1, this entry maps a 2MB page.
    uint64 global: 1;               // if 1, page is global
    uint64 Ignored2 : 3;
    uint64 frame : 40;     // The page frame number of the PT of this PDE.
    uint64 Ignored3 : 11;
    uint64 ExecuteDisable : 1;       // If 1, instruction fetches not allowed.
} pml4_entry_t;

typedef struct __pdpt_entry__
{
    uint64 present : 1;              // Must be 1, region invalid if 0.
    uint64 rw : 1;            // If 0, writes not allowed.
    uint64 supervisor : 1;       // If 0, user-mode accesses not allowed.
    uint64 PageWriteThrough : 1;     // Determines the memory type used to access PT.
    uint64 PageCacheDisable : 1;     // Determines the memory type used to access PT.
    uint64 Accessed : 1;             // If 0, this entry has not been used for translation.
    uint64 dirty : 1;
    uint64 pagesize : 1;             // If 1, this entry maps a 2MB page.
    uint64 global: 1;               // if 1, page is global
    uint64 Ignored2 : 3;
    uint64 frame : 40;     // The page frame number of the PT of this PDE.
    uint64 Ignored3 : 11;
    uint64 ExecuteDisable : 1;       // If 1, instruction fetches not allowed.
} pdpt_entry_t;

typedef struct __pd_entry__
{
    uint64 present : 1;              // Must be 1, region invalid if 0.
    uint64 rw : 1;            // If 0, writes not allowed.
    uint64 supervisor : 1;       // If 0, user-mode accesses not allowed.
    uint64 PageWriteThrough : 1;     // Determines the memory type used to access PT.
    uint64 PageCacheDisable : 1;     // Determines the memory type used to access PT.
    uint64 Accessed : 1;             // If 0, this entry has not been used for translation.
    uint64 dirty : 1;
    uint64 pagesize : 1;             // If 1, this entry maps a 2MB page.
    uint64 global: 1;               // if 1, page is global
    uint64 Ignored2 : 3;
    uint64 frame : 40;     // The page frame number of the PT of this PDE.
    uint64 Ignored3 : 11;
    uint64 ExecuteDisable : 1;       // If 1, instruction fetches not allowed.
} pd_entry_t;

typedef struct __pt_entry__
{
    uint64 present : 1;              // Must be 1, region invalid if 0.
    uint64 rw : 1;            // If 0, writes not allowed.
    uint64 supervisor : 1;       // If 0, user-mode accesses not allowed.
    uint64 PageWriteThrough : 1;     // Determines the memory type used to access PT.
    uint64 PageCacheDisable : 1;     // Determines the memory type used to access PT.
    uint64 Accessed : 1;             // If 0, this entry has not been used for translation.
    uint64 dirty : 1;
    uint64 pagesize : 1;             // If 1, this entry maps a 2MB page.
    uint64 global: 1;               // if 1, page is global
    uint64 Ignored2 : 3;
    uint64 frame : 40;     // The page frame number of the PT of this PDE.
    uint64 Ignored3 : 11;
    uint64 ExecuteDisable : 1;       // If 1, instruction fetches not allowed.
} pt_entry_t;

/* 
** this MMU use a reference pointer table
** take a lot of memory but will be scalable
*/

typedef struct __pt_t__
{
    pt_entry_t page[512];
} pt_t;

typedef struct __pd_t__
{
    pd_entry_t entry[512];
    pt_t *ref[512];
} pd_t;


typedef struct __pdpt_t__
{
    pdpt_entry_t entry[512];
    pd_t *ref[512];
} pdpt_t;

typedef struct __pml4_t__
{
    pml4_entry_t entry[512];
    pdpt_t *ref[512];
} pml4_t;

#endif