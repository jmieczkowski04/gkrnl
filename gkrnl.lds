ENTRY("start")
OUTPUT_ARCH("i386")
OUTPUT_FORMAT("elf32-i386")
SECTIONS {
    . = 0x00100000;

    .multiboot.data : {
        *(.multiboot.data)
    }

    .multiboot.text : {
       *(.multiboot.text)
    }

    /* . = 0xC0000000; */
    .text ALIGN(4K) : {
        *(.text)
    }

    .data ALIGN(4K) : {
        *(.data)
    }

    .rodata ALIGN(4K) : {
        *(.rodata)
    }

    .bss ALIGN(4K) : {
        *(.bss)
        *(.boot_stack)
    }
}