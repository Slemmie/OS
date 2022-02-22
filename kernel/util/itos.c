// implementation of converting int to char*

// table for converting digit to char
const char DIGIT_TO_CHAR[] = "0123456789abcdef";

int itos(int value, char* buffer, int base) {
	// check for violating possible base ranges
	if (base * (base < 0 ? -1 : 1) < 2 || base * (base < 0 ? -1 : 1) > 16) {
		return 1;
	}
	
	int ptr = 0;
	
	if (base > 0) { // signed mode
		// extract digits
		int neg = 0;
		if (value < 0) {
			neg = 1;
			value = -value;
		}
		do {
			int digit = value % base;
			buffer[ptr++] = DIGIT_TO_CHAR[digit];
			value /= base;
		} while (value);
		if (neg) {
			buffer[ptr++] = '-';
		}
	} else { // unsigned mode
		base = -base;
		// extract digits
		unsigned int uvalue = (unsigned int) value;
		do {
			int digit = uvalue % base;
			buffer[ptr++] = DIGIT_TO_CHAR[digit];
			uvalue /= base;
		} while (uvalue);
	}
	
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
