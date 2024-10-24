#include "boot/multiboot.h"
#define STACK_SIZE 0x4000
#define MB_FLAGS (MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO)	

	.code32
	.section .multiboot.data, "aw"
multiboot_header:
	.align 4
	.long MULTIBOOT_HEADER_MAGIC
	.long MB_FLAGS
	.long -(MULTIBOOT_HEADER_MAGIC + MB_FLAGS)

	.section .boot_stack, "aw", @nobits
stack:
	.skip STACK_SIZE

	.section .bss, "aw", @nobits
	.align 4096
boot_page_directory:
	.skip 4096
boot_page_table1:
	.skip 4096


	.section .multiboot.text, "a"
	.globl start
start:
	movl $(boot_page_table1 - 0xC0000000), %edi
	movl $0, %esi
	movl $1023, %ecx

1:
	cmpl $_kernel_start, %esi
	jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)
2:
	addl $4096, %esi
	addl $4,%edi
	decl %ecx
	jnz 1b
3:
	movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 * 4
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4
	movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	lea 4f, %ecx
	jmp *%ecx

	.section .text
4:
	movl $0, boot_page_directory + 0

	movl %cr3, %ecx
	movl %ecx, %cr3

	movl $(stack + STACK_SIZE), %esp
	pushl $0
	popf

	/* .extern vm_boot32_main
	pushl %ebx
	pushl %eax
	call vm_boot32_main */
hlt_loop:
	hlt
	jmp hlt_loop
