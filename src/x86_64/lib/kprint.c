#include "eternity.h"
#include "stdarg.h"

long power(long max, int power)
{
    long ret = power;

    for (; max != 0x2; max--)
        ret *= power;
    return (ret);
}

void putchar(char c)
{
    vga_putchar(c);
}

void puts(char const *s)
{
    for (; *s; s++)
        putchar(*s);
}

void hexa_put(ulong n)
{
    ulong max = 0x0, ch = 0x0, save = n;

    puts("0x");
    for (; n / 0x10 > 0; n /= 0x10, max++);
    for (; (long)max >= 0; max--) {
        ch = n % 0x10;
        if (ch > 0x9)
            putchar(0x41 + (ch - 0xA));
        else
            putchar(ch + 0x30);
        if (max == 0x0 || max == 0x1)
            n = save;
        else
            n = save / power(max, 0x10);
    }
}

void bin_put(long n)
{
    long max = 0x0, ch = 0x0, save = n;

    if (n < 0) {
        putchar('-');
        n *= -0x1;
    }
    vga_putstr("0b");
    for (; n / 0x2 > 0; n /= 0x2, max++);
    for (; max >= 0; max--) {
        ch = n % 0x2;
        putchar(ch + 0x30);
        if (max == 0x0 || max == 0x1)
            n = save;
        else
            n = save / power(max, 0x2);
    }
}

void int_put(int n)
{
    int mod = 0xA, sub = 0x0, cur = 0x0;

    if (n < 0x0) {
        putchar('-');
        n *= -0x1;
    }
    for (; n % mod != n; mod *= 0XA);
    for (; mod != 0x1; mod /= 0xA) {
        sub = (n % (mod / 0xA));
        cur = ((n % mod) - sub) / (mod / 0XA);
        putchar(cur + 0x30);
    }
}

void long_put(long n)
{
    long mod = 0xA, sub = 0x0, cur = 0x0;

    if (n < 0x0) {
        putchar('-');
        n *= -0x1;
    }
    for (; n % mod != n; mod *= 0XA);
    for (; mod != 0x1; mod /= 0xA) {
        sub = (n % (mod / 0xA));
        cur = ((n % mod) - sub) / (mod / 0XA);
        putchar(cur + 0x30);
    }
}

void float_put(double n, int prec)
{
    int zero = 0x0;
    long part = (long)n;

    if (prec > 0x9 || prec < 0x0)
        return;
    if (n < 0x0) {
        n *= -0x1;
        putchar('-');
        part = (long)n;
    }
    prec = power(prec + 1, 0xA);
    long_put(part);
    n = n - part;
    putchar(',');
    if ((long)(n * 0xA) == 0x0) {
        for (double tmp = n; tmp != 0x0 && (long)tmp == 0x0; zero++, tmp *= 0xA);
        for (; zero > 0x1; zero--)
            putchar(0x30);
    }
    n *= prec;
    long_put((long)n);
}

void switch_types(char const *format, va_list ap, int *i)
{
    /* FLAGS HANDLE BY THIS PRINTF */
    switch (format[*i]) {
        case 's':
            vga_putstr(va_arg(ap, char *));
            break;
        case 'd':
            int_put(va_arg(ap, int));
            break;
        case 'x':
            hexa_put(va_arg(ap, ulong));
            break;
        case 'l':
            long_put(va_arg(ap, long));
            break;
        case 'c':
            putchar(va_arg(ap, int));
            break;
        case 'b':
            bin_put(va_arg(ap, long));
            break;
        case '%':
            putchar('%');
            break;
        case 'f':
            float_put(va_arg(ap, double), format[*i + 0x1] - 0x30);
            *i += 0x1;
            break;
        default: // unknow flag => print this
            putchar('%');
            putchar(format[*i]);
    }
}

void kprint(char const *format, ...)
{
    va_list ap;

    va_start(ap, format);
    for (int i = 0x0; format[i] ; i++) {
        if (format[i] != '%')
            putchar(format[i]);
        else {
            i++;
            switch_types(format, ap, &i);
        }
    }
    va_end(ap);
}

void kvprint(char const *format, va_list ap)
{
    for (int i = 0x0; format[i] ; i++) {
        if (format[i] != '%')
            putchar(format[i]);
        else {
            i++;
            switch_types(format, ap, &i);
        }
    }
}
