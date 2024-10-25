#include "drivers/pic/pic.h"


void pic_init(void)
{
    remap_pic_irqs(0x20, 0x28);
    disable_all_pic_irq();
}