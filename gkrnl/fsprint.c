#include "gkrnl/fsprint.h"
#include "gkrnl/primitives.h"

#define FLAG_SIGN (1<<7)

static char* number_to_str(char* str, uint32_t number, uint8_t base, uint8_t flags);


void fsprint(char* buffer, const char* fmt, va_list vargs)
{
    char* str = buffer;
    char* s;
    for (int i = 0; fmt[i]; ++i)
    {
        if (fmt[i] != '%')
        {
            *str++ = fmt[i];
            continue;
        }
        switch (fmt[++i])
        {
        case 'c':
            *str++ = (unsigned char)va_arg(vargs, int);
            break;
        case 's':
            s = va_arg(vargs, char*);
            for (;*s; ++s)
            {
                *str++ = *s;
            }
            break;
        case 'o':
            str = number_to_str(str, va_arg(vargs, uint32_t), 8, 0);
            break;
        case 'x':
            str = number_to_str(str, va_arg(vargs, uint32_t), 16, 0);
            break;
        case 'd':
            str = number_to_str(str, va_arg(vargs, uint32_t), 10, FLAG_SIGN);
            break;
        case 'u':
            str = number_to_str(str, va_arg(vargs, uint32_t), 10, 0);
            break;
        case 'p':
            str = number_to_str(str, (uint32_t)va_arg(vargs, void*), 16, 0);
            break;
        case '%':
            *str++ = '%';
            break;
        case '\0':
            --i;
            break;
        default:
            *(str++) = fmt[i];
            break;
        }
    }
    *str = '\0';
}

static char* number_to_str(char* str, uint32_t number, uint8_t base, uint8_t flags)
{
    const char* digits = "0123456789ABCDEF";
    char tmp[32];
    int32_t snumber = (int32_t)number;
    if (!number)
    {
        *(str++) = '0';
    }
    if (flags & FLAG_SIGN && snumber < 0)
    {
        number = (uint32_t)(-(int32_t)number);
    }
    int i;
    for (i = 0; number; ++i)
    {
        switch (base)
        {
        case 8:
            tmp[i] = digits[number & 7];
            number = number >> 3;
            break;
        
        case 10:
            tmp[i] = digits[number % 10];
            number = number / 10;
            break;
        
        case 16:
            tmp[i] = digits[number & 0xF];
            number = number >> 4;
            break;
        default:
            return str;
        }
    }

    if(flags & FLAG_SIGN)
    {
        if (snumber < 0)
        {
            tmp[i++] = '-';
        }
    }
    while(i-->0)
    {
        *str++ = tmp[i];
    }
    return str;
}
