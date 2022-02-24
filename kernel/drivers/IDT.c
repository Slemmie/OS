 //TODO: handle scancode conversion + rest of interrupts

#include "IDT.h"

#include "../port_io.h"

#include "../vidmem/vidmem.h"

extern IDT_64 _idt[256];

extern uint_64 isr1;

extern void load_IDT();

void initialize_IDT() {
	vidmem_puts("hello.\n");
	
	for(uint_64 i = 0; i < 256; ++i) {
		_idt[i].zero = 0;
		_idt[i].offset_low  = (uint_16) (((uint_64) &isr1));
		_idt[i].offset_mid  = (uint_16) (((uint_64) &isr1) >> 16);
		_idt[i].offset_high = (uint_32) (((uint_64) &isr1) >> 32);
		_idt[i].ist = 0;
		_idt[i].selector = 0x08;
		_idt[i].types_attr = 0x8e;
	}
	
	port_byte_out(0x21, 0xfd);
	port_byte_out(0xa1, 0xff);
	
	load_IDT();
}

extern void _isr1_handler() {
	// print keyboard input on interrupt
	// abstract out later
	vidmem_put_int(port_byte_in(0x60), 16);
	
	port_byte_out(0x20, 0x20);
	port_byte_out(0xa0, 0x20);
}
