#include "drivers/pic/pic.h"
#include "gkrnl/io.h"
#include "pic_defs.h"

void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8)
        outb(SPIC_COMMAND, PIC_EOI);
    outb(MPIC_COMMAND, PIC_EOI);
}