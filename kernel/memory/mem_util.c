// implementation of memory utility functions
// such as memset, memcpy, etc. (rather than malloc stuff)

#include "memory.h"

// set every byte in a block of memory to value
void memset(void* ptr, unsigned char value, unsigned int size) {
	unsigned char* arr = (unsigned char*) ptr;
	for (unsigned int i = 0; i < size; i++) {
		*(arr + i) = value;
	}
}

// copy memory from one block to another
void memcpy(void* dest, void* src, unsigned int size) {
	unsigned char* dest_b = (unsigned char*) dest;
	unsigned char* src_b = (unsigned char*) src;
	
	for (unsigned int i = 0; i < size; i++) {
		*(dest_b + i) = *(src_b + i);
	}
}
