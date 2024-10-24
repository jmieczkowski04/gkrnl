#include "boot/multiboot.h"
#define STACK_SIZE 0x4000
#define MB_FLAGS (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO)	

	.code32
	.align 4
	.section .multiboot.data, "aw"
multiboot_header:
	.long MULTIBOOT_HEADER_MAGIC
	.long MB_FLAGS
	.long -(MULTIBOOT_HEADER_MAGIC + MB_FLAGS)
	.long 0
	.long 0
	.long 0
	.long 0
	.long 0

	.long 0
	.long 0
	.long 0
	.long 0

	.section .boot_stack, "aw", @nobits
stack:
	.skip STACK_SIZE

	.section .bss, "aw", @nobits
	.align 4096

	.section .multiboot.text, "a"
	.globl start
start:
	movl $(stack + STACK_SIZE), %esp
	pushl $0
	popf

	pushl %ebx
	pushl %eax
hlt_loop:
	hlt
	jmp hlt_loop
