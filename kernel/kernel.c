// kernel written in C

#include "vid_mem.h"

#include "util/util.h"

#include "memory/memory.h"

void main() {
	
	vidmem_clear_screen();
	vidmem_set_cursor(0, 0);
	
	init_paging();
	
}
