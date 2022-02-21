// kernel written in C

void main() {
	// sample program
	// write a character to vid-mem
	
	char* video_memory_address = (char*) 0xb8000;
	
	*video_memory_address = 'X';
}
