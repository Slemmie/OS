// KAINEL ENTRY

#include "util/types.h"
#include "util/algorithm.h"

void _start() {
	char c1 = 'h';
	char c2 = 'i';
	
	swap(c1, c2);
	
	*((uint_8*) 0xb8000) = (uint_8) c1;
	*((uint_8*) 0xb8001) = (uint_8) 0x0f;
	*((uint_8*) 0xb8002) = (uint_8) c2;
	*((uint_8*) 0xb8003) = (uint_8) 0x0f;
}
