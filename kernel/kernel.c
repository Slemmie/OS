// KAINEL ENTRY

#define VIDMEM_SIMPLIFIED_API
#include "vidmem/vidmem.h"

#include "FPU.h"

#include "drivers/IDT.h"

void _start() {
	clear_screen_color(BG_BLUE | FG_WHITE);
	set_cursor(0, 0);
	
	enable_FPU();
	
	initialize_IDT();
	
	char* str = "abcd hello\n\nwith hey, ho, the\nwind\n\n\n       and the rain\n\n    :)\n";
	puts(str);
	puts_color(str, FG_PURPLE);
	
	putchar('\n');
	
	put_int(0xfec71a09b, 16);
}
