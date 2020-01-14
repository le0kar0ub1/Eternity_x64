#ifndef _ETERNITY_DEF_H_
#define _ETERNITY_DEF_H_

#include "kconfig.h"

#define asmv __asm__ volatile

#if FATAL_ASSERT
    #define fatalAssert(expr)   \
            if (unexpected(!(expr))) \
                PANIC("assert(%s) failed in %s at line %d.\n", \
                #expr, __FILE__, __LINE__);
#else
    #define fatalAssert(expr) expr
#endif
/* PANIC IF ASSERT FAILED */
#define assert_eq(a, b)  fatalAssert((a) == (b))
#define assert_ne(a, b)  fatalAssert((a) != (b))
#define assert_lg(a, b)  fatalAssert((a) < (b))
#define assert_le(a, b)  fatalAssert((a) <= (b))
#define assert_gt(a, b)  fatalAssert((a) > (b))
#define assert_ge(a, b)  fatalAssert((a) > (b))

/* C11 KEYWORD SHORTCUT */
#define restrict      __restrict
#define __pure        __attribute__((pure))
#define __const       __attribute__((const))
#define __cold        __attribute__((cold))
#define __hot         __attribute__((hot))
#define __used        __attribute__((used))
#define __unused      __attribute__((unused))
#define __packed      __attribute__((packed))
#define __weak        __attribute__((weak))
#define __aligned(x)  __attribute__((aligned (x)))
#define __section(s)  __attribute__((section (s)))
#define __noreturn    __attribute__((noreturn))
#define expected(x)   __builtin_expect((x), 1)
#define unexpected(x) __builtin_expect((x), 0)
#define __optimize(x) __attribute__((optimize(x)))

#define PAGE_SIZE  0x1000
#define FRAME_SIZE 0x1000

#define ALIGN(x, y)        (((x) + ((y) - 1)) & ~((y) - 1))
#define ALIGN_PAGE(x)      (ALIGN(x, PAGE_SIZE))
#define ALIGN_FRAME(x)     (ALIGN(x, FRAME_SIZE))
#define IS_PAGE_ALIGNED(x) (!((uintptr)(x) & (PAGE_SIZE - 0x1)))

#endif
