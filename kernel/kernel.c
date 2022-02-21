// kernel written in C

#include "vid_mem.h"

void main() {
	// sample program
	// write a character to vid-mem
	
	vidmem_clear_screen();
	vidmem_set_cursor(0, 0);
	vidmem_puts("Hello world!\n", 0);
	
}
