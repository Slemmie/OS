// implementation of communication with I/O bus addresses

#include "port_io.h"

#include "util/types.h"

uint_8 port_byte_in(IO_port port) {
	uint_8 result;
	__asm__ volatile ("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}

void port_byte_out(IO_port port, uint_8 data) {
	__asm__ volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}

void remap_pic() {
	uint_8 a1 = port_byte_in(PIC1_DATA);
	uint_8 a2 = port_byte_in(PIC2_DATA);
	
	port_byte_out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	port_byte_out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	port_byte_out(PIC1_DATA, 0);
	port_byte_out(PIC2_DATA, 8);
	port_byte_out(PIC1_DATA, 4);
	port_byte_out(PIC2_DATA, 2);
	port_byte_out(PIC1_DATA, ICW4_8086);
	port_byte_out(PIC2_DATA, ICW4_8086);
	
	port_byte_out(PIC1_DATA, a1);
	port_byte_out(PIC2_DATA, a2);
}
