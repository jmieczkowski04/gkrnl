#include "gkrnl/idt.h"
#include "gkrnl/primitives.h"
#include "boot/multiboot.h"
#include "mm/gdt.h"
#include "drivers/pic/pic.h"
#include "drivers/vga/vga.h"



void vm_boot32_main(uint32_t mb_magic, void* mb_info_phys_addr)
{
    vga_init();
    if (mb_magic != MULTIBOOT_BOOTLOADER_MAGIC)
    {
        vga_print("Kernel boot error!\n");
        return;
    }
    gdt_init();
    pic_init();
    idt_init();
    vga_print("Sonne!");
    
    for(;;);
    return;
}