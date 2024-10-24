#ifndef _VGA_H_
#define _VGA_H_

#include "gkrnl/primitives.h"

void vga_init(void);
void vga_cls(void);
void vga_print(const char* str);


#endif /*_VGA_H_*/