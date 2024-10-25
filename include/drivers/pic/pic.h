#ifndef _PIC_H_
#define _PIC_H_

#include "gkrnl/primitives.h"

void pic_init(void);
void disable_all_pic_irq(void);
void disable_pic_irq(uint8_t irq);
void enable_pic_irq(uint8_t irq);
void pic_send_eoi(uint8_t irq);
void remap_pic_irqs(int offset_master, int offset_slave);

#endif /*_PIC_H_*/