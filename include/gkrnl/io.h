#ifndef _IO_H_
#define _IO_H_

#include "gkrnl/primitives.h"

static inline volatile uint8_t inb(uint16_t port)
{
    uint8_t v;

    __asm__ volatile( "inb %w1, %b0"
                   : "=a"(v)
                   : "Nd"(port)
                   : "memory");
    return v;
}

static inline volatile void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
}

static inline void io_wait(void)
{
    outb(0x80, 0);
}

#endif /*_IO_H_*/