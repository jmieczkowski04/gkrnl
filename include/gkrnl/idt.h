#ifndef _IDT_H_
#define _IDT_H_

#include "gkrnl/primitives.h"

#define DPL_KERNEL 0x00
#define DPL_USER 0x03
#define GATE_INTERRPUT 0x0E
#define GATE_TRAP 0x0F

void idt_init(void);
void set_idt_desc(uint16_t entry_id, void* irs, uint8_t dpl, uint8_t gate_type);

#define INTERRPUT_GATE(irq_no, addr) set_idt_desc(irq_no, addr, DPL_KERNEL, GATE_INTERRPUT)
#define TRAP_GATE(irq_no, addr) set_idt_desc(irq_no, addr, DPL_KERNEL, GATE_TRAP)
#define SYSCALL_GATE(irq_no, addr) set_idt_desc(irq_no, addr, DPL_USER, GATE_TRAP)

#endif /*_IDT_H_*/