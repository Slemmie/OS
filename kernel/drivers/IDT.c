 //TODO: handle scancode conversion + rest of interrupts

#include "IDT.h"

#include "../port_io.h"

#include "../vidmem/vidmem.h"

extern IDT_64 _idt[256];

extern uint_64 isr1;

extern void load_IDT();

void initialize_IDT() {
	_idt[1].zero = 0;
	_idt[1].offset_low  = (uint_16) (((uint_64) &isr1));
	_idt[1].offset_mid  = (uint_16) (((uint_64) &isr1) >> 16);
	_idt[1].offset_high = (uint_32) (((uint_64) &isr1) >> 32);
	_idt[1].ist = 0;
	_idt[1].selector = 0x08;
	_idt[1].types_attr = 0x8e;
	
	remap_pic();
	
	port_byte_out(0x21, 0xfd);
	port_byte_out(0xa1, 0xff);
	
	load_IDT();
}

#include "keyboard/US.h"

extern void _isr1_handler() {
	// print keyboard input on interrupt
	// abstract out later
	uint_8 key = port_byte_in(0x60);
	
	char cha = us_kb_char(key);
	if(cha != '\0')	vidmem_putchar(cha);
	
	port_byte_out(0x20, 0x20);
	port_byte_out(0xa0, 0x20);
}
