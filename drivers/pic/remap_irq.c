
#include "drivers/pic/pic.h"
#include "gkrnl/primitives.h"
#include "gkrnl/io.h"
#include "pic_defs.h"

void remap_pic_irqs(int offset_master, int offset_slave)
{
    uint8_t old_mask_master, old_mask_slave;
    old_mask_master = inb(MPIC_DATA);
    old_mask_slave = inb(SPIC_DATA);

    outb(MPIC_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	io_wait();
	outb(SPIC_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(MPIC_DATA, offset_master);                 // ICW2: Master PIC vector offset
	io_wait();
	outb(SPIC_DATA, offset_slave);                 // ICW2: Slave PIC vector offset
	io_wait();
	outb(MPIC_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	io_wait();
	outb(SPIC_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	io_wait();
 
	outb(MPIC_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	io_wait();
	outb(SPIC_DATA, ICW4_8086);
	io_wait();
 
	outb(MPIC_DATA, old_mask_master);   // restore saved masks.
	outb(SPIC_DATA, old_mask_slave);
}