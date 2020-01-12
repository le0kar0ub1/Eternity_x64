#include "ports.h"
#include "stdarg.h"

long serial_power(long max, int power)
{
    long ret = power;

    for (; max != 0x2; max--)
        ret *= power;
    return (ret);
}

void serial_putchar(char c)
{
    write_serial(c);
}

void serial_puts(char const *s)
{
    for (; *s; s++)
        serial_putchar(*s);
}

void serial_hexa_put(ulong n)
{
    ulong max = 0x0, ch = 0x0, save = n;

    serial_puts("0x");
    for (; n / 0x10 > 0; n /= 0x10, max++);
    for (; (long)max >= 0; max--) {
        ch = n % 0x10;
        if (ch > 0x9)
            serial_putchar(0x41 + (ch - 0xA));
        else
            serial_putchar(ch + 0x30);
        if (max == 0x0 || max == 0x1)
            n = save;
        else
            n = save / serial_power(max, 0x10);
    }
}

void serial_bin_put(long n)
{
    long max = 0x0, ch = 0x0, save = n;

    if (n < 0) {
        serial_putchar('-');
        n *= -0x1;
    }
    serial_putstr("0b");
    for (; n / 0x2 > 0; n /= 0x2, max++);
    for (; max >= 0; max--) {
        ch = n % 0x2;
        serial_putchar(ch + 0x30);
        if (max == 0x0 || max == 0x1)
            n = save;
        else
            n = save / serial_power(max, 0x2);
    }
}

void serial_int_put(int n)
{
    int mod = 0xA, sub = 0x0, cur = 0x0;

    if (n < 0x0) {
        serial_putchar('-');
        n *= -0x1;
    }
    for (; n % mod != n; mod *= 0XA);
    for (; mod != 0x1; mod /= 0xA) {
        sub = (n % (mod / 0xA));
        cur = ((n % mod) - sub) / (mod / 0XA);
        serial_putchar(cur + 0x30);
    }
}

void serial_long_put(long n)
{
    long mod = 0xA, sub = 0x0, cur = 0x0;

    if (n < 0x0) {
        serial_putchar('-');
        n *= -0x1;
    }
    for (; n % mod != n; mod *= 0XA);
    for (; mod != 0x1; mod /= 0xA) {
        sub = (n % (mod / 0xA));
        cur = ((n % mod) - sub) / (mod / 0XA);
        serial_putchar(cur + 0x30);
    }
}

void serial_float_put(double n, int prec)
{
    int zero = 0x0;
    long part = (long)n;

    if (prec > 0x9 || prec < 0x0)
        return;
    if (n < 0x0) {
        n *= -0x1;
        serial_putchar('-');
        part = (long)n;
    }
    prec = serial_power(prec + 1, 0xA);
    serial_long_put(part);
    n = n - part;
    serial_putchar(',');
    if ((long)(n * 0xA) == 0x0) {
        for (double tmp = n; tmp != 0x0 && (long)tmp == 0x0; zero++, tmp *= 0xA);
        for (; zero > 0x1; zero--)
            serial_putchar(0x30);
    }
    n *= prec;
    serial_long_put((long)n);
}

void serial_switch_types(char const *format, va_list ap, int *i)
{
    /* FLAGS HANDLE BY THIS PRINTF */
    switch (format[*i]) {
        case 's':
            serial_putstr(va_arg(ap, char *));
            break;
        case 'd':
            serial_int_put(va_arg(ap, int));
            break;
        case 'x':
            serial_hexa_put(va_arg(ap, ulong));
            break;
        case 'l':
            serial_long_put(va_arg(ap, long));
            break;
        case 'c':
            serial_putchar(va_arg(ap, int));
            break;
        case 'b':
            serial_bin_put(va_arg(ap, long));
            break;
        case '%':
            serial_putchar('%');
            break;
        case 'f':
            serial_float_put(va_arg(ap, double), format[*i + 0x1] - 0x30);
            *i += 0x1;
            break;
        default: // unknow flag => print this
            serial_putchar('%');
            serial_putchar(format[*i]);
    }
}

void serial_kprint(char const *format, ...)
{
    va_list ap;

    va_start(ap, format);
    for (int i = 0x0; format[i] ; i++) {
        if (format[i] != '%')
            serial_putchar(format[i]);
        else {
            i++;
            serial_switch_types(format, ap, &i);
        }
    }
    va_end(ap);
}