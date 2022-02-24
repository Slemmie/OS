// implementation of communication with I/O bus addresses

#include "port_io.h"

uint_8 port_byte_in(IO_port port) {
	uint_8 result;
	__asm__ volatile ("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}

void port_byte_out(IO_port port, uint_8 data) {
	__asm__ volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}
