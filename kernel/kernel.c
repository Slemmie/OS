// kernel written in C

void pr(int id, short value) {
	((char*)0x000b8002)[id * 2] = value;
}

void main() {
	// sample program
	// write a character to vid-mem
	
	long int place = 0;
	pr(place, 'H');
	
}
