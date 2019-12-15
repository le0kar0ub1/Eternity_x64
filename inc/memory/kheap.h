#ifndef _MALLOK_H_
#define _MALLOK_H_

void *internal_mallok(uint64 sz, int align, uint64 *phys);
void kfree(uintptr *free);
void *mallok(uint64 sz);

#endif
