// KAINEL ENTRY

#define VIDMEM_SIMPLIFIED_API
#include "vidmem/vidmem.h"

#include "FPU.h"

void _start() {
	enable_FPU();
	
	clear_screen();
	set_cursor(0, 0);
	
	char* str = "abcd hello\n\nwith hey, ho, the\nwind\n\n\n       and the rain\n\n    :)\n";
	puts(str);
	puts_color(str, FG_PURPLE);
	
	putchar('\n');
	
	put_int(0xfec71a09b, 16);
}
