#include "drivers/vga/vga.h"



void vm_boot32_main()
{
    vga_init();
    vga_print("Sonne!");
    for(;;);
    return;
}