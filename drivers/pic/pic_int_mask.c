#include "drivers/pic/pic.h"
#include "gkrnl/primitives.h"
#include "gkrnl/io.h"
#include "pic_defs.h"

static uint8_t master_pic_cached_mask;
static uint8_t slave_pic_cached_mask;

static void update_pic_mask(uint8_t is_master);

void disable_all_pic_irq(void)
{
    master_pic_cached_mask = 0xFF;
    slave_pic_cached_mask = 0xFF;
    update_pic_mask(1);
    update_pic_mask(0);
}

void enable_pic_irq(uint8_t irq)
{
    if (irq < 8)
    {
        master_pic_cached_mask &= ~(1 << irq);
        update_pic_mask(1);
    }
    else
    {
        slave_pic_cached_mask &= ~(1 << (irq-8));
        update_pic_mask(0);
    }
}

void disable_pic_irq(uint8_t irq)
{
    if (irq < 8)
    {
        master_pic_cached_mask |= (1 << irq);
        update_pic_mask(1);
    }
    else
    {
        master_pic_cached_mask |= (1 << irq);
        update_pic_mask(1);
    }
}

static void update_pic_mask(uint8_t is_master)
{
    if(is_master)
    {
        outb(MPIC_DATA, master_pic_cached_mask);
    }
    else
    {
        outb(MPIC_DATA, slave_pic_cached_mask);
    }
}