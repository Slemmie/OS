// KAINEL ENTRY

extern "C" void _start() {
	char* vidmem = (char*) 0xb8000;
	for (int i = 0; i < 25 * 80; i++) {
		vidmem[i] = 0x1f20;
	}
	return;
}
