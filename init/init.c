#include "gkrnl/idt.h"
#include "gkrnl/primitives.h"
#include "gkrnl/printk.h"
#include "boot/multiboot.h"
#include "mm/gdt.h"
#include "drivers/pic/pic.h"
#include "drivers/vga/vga.h"
#include "sse.h"



void vm_boot32_main(uint32_t mb_magic, void* mb_info_phys_addr)
{
    vga_init();
    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        printk("Kernel boot error! EAX: %x\n", mb_magic);
        return;
    }
    if(!check_for_sse_support())
    {
        printk("SSE support is required! Halting");
        return;
    }
    gdt_init();
    pic_init();
    idt_init();
    enable_sse();
    printk("Sonne! %x", mb_magic);

    for(;;);
    return;
}