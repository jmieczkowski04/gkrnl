#ifndef __PIC_DEFS_H_
#define __PIC_DEFS_H_

#define MPIC_COMMAND 0x20
#define MPIC_DATA (MPIC_COMMAND + 1)
#define SPIC_COMMAND 0xA0
#define SPIC_DATA (SPIC_COMMAND + 1)

#define PIC_EOI	0x20

#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#endif /*__PIC_DEFS_H_*/