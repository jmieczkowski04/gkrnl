#include "gkrnl/printk.h"
#include "gkrnl/fsprint.h"
#include "drivers/vga/vga.h"

#include <stdarg.h>

#define BUFF_SIZE 1024

static char buff[BUFF_SIZE];

void printk(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fsprint(buff, fmt, args);
    va_end(args);
    vga_print(buff);
}