// implementation of converting int to char*

// table for converting digit to char
const char DIGIT_TO_CHAR[] = "0123456789abcdef";

int itos(int value, char* buffer, int base) {
	// check for violating possible base ranges
	if (base < 2 || base > 16) {
		return 1;
	}
	
	// extract digits
	int ptr = 0;
	do {
		int digit = value % base;
		buffer[ptr++] = DIGIT_TO_CHAR[digit];
		value /= base;
	} while (value);
	
	// reverse string
	for (int i = 0; i < ptr / 2; i++) {
		// swap values
		int tmp = buffer[i];
		buffer[i] = buffer[ptr - i - 1];
		buffer[ptr - i - 1] = tmp;
	}
	
	// set null terminator
	buffer[ptr] = '\0';
	
	return 0;
}
