// enable floating point unit

#include "util/types.h"

void enable_FPU() {
	uint_64 cr4;
	__asm__ volatile ("mov %%cr4, %0" : "=r"(cr4));
	cr4 |= 0x200;
	__asm__ volatile ("mov %0, %%cr4" : : "r"(cr4));
	uint_16 control_word = 0x37F;
	__asm__ volatile ("fldcw %0" : : "m"(control_word));
}
