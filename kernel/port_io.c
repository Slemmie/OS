// implementation of communication with I/O addresses

#include "port_io.h"

unsigned char port_byte_in(IO_port port) {
	unsigned char result ;
	__asm__ ("in %%dx, %%al" : "=a" (result) : "d" (port));
	return result ;
}

unsigned short port_word_in(IO_port port) {
	unsigned short result ;
	__asm__ ("in %%dx, %%ax" : "=a" (result) : "d" (port));
	return result ;
}

void port_byte_out(IO_port port, unsigned char data) {
	__asm__ ("out %%al, %%dx" : : "a" (data), "d" (port));
}

void port_word_out(IO_port port, unsigned short data) {
	__asm__ ("out %%ax, %%dx" : : "a" (data), "d" (port));
}
