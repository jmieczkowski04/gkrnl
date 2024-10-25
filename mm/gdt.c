#include "mm/gdt.h"
#include "gkrnl/primitives.h"

#define GDT_LEN 5
typedef struct gdt_desc
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_hi;
} __attribute__((packed)) gdt_desc_t;

typedef struct gdt_header
{
    uint16_t size;
    uint32_t addr;
} __attribute__((packed)) gdt_header_t;


static void set_gdt_selector(gdt_desc_t* selector, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
extern void load_gdt(gdt_header_t* ptr);
static gdt_desc_t gdt[GDT_LEN];
static gdt_header_t gdt_head;

void gdt_init(void)
{
    set_gdt_selector(&gdt[0], 0, 0, 0, 0);
    set_gdt_selector(&gdt[1], 0, 0xFFFFFFFF, 0x9B, 0xCF); // ring0 code
    set_gdt_selector(&gdt[2], 0, 0xFFFFFFFF, 0x93, 0xCF); // ring0 data
    set_gdt_selector(&gdt[3], 0, 0xFFFFFFFF, 0xFB, 0xCF);
    set_gdt_selector(&gdt[4], 0, 0xFFFFFFFF, 0xF3, 0xCF);

    gdt_head.addr = (uint32_t)&gdt;
    gdt_head.size = sizeof(gdt_desc_t) * GDT_LEN - 1;
    load_gdt(&gdt_head);
}

static void set_gdt_selector(gdt_desc_t* selector, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    selector->base_low = base & 0xFFFF;
    selector->base_mid = (base >> 16) & 0xFF;
    selector->base_hi = (base >> 24);
    selector->limit_low = limit & 0xFFFF;
    selector->granularity = (((limit >> 16) & 0xF) | (granularity & 0xF0));
    selector->access = access;
}