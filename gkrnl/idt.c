#include "gkrnl/idt.h"
#include "gkrnl/primitives.h"

#define IDT_LEN 255

typedef struct idt_header
{
    uint16_t size;
    uint32_t addr;
} __attribute__((packed)) idt_header_t;

typedef struct idt_entry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

static idt_header_t idt_head;
static idt_entry_t idt[IDT_LEN];

extern void load_idt(idt_header_t* ptr);

void idt_init(void)
{
    idt_head.addr = (uint32_t)&idt;
    idt_head.size = sizeof(idt_entry_t) * IDT_LEN - 1;
    load_idt(&idt_head);
    __asm__ volatile("sti");
}

void set_idt_desc(uint16_t entry_id, void* irs, uint8_t dpl, uint8_t gate_type)
{
    uint32_t offset = (uint32_t)irs;
    idt[entry_id].reserved = 0;
    idt[entry_id].offset_low = offset & 0xFFFF;
    idt[entry_id].offset_high = (offset >> 16) & 0xFFFF;
    idt[entry_id].selector = 0x08;
    idt[entry_id].attributes = 0x80 | ((dpl & 0x3) << 5) | (gate_type & 0xF);
}