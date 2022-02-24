#pragma once

#include "../util/types.h"

typedef struct IDT64{
	uint_16 offset_low;
	uint_16 selector;
	uint_8 ist;
	uint_8 types_attr;
	uint_16 offset_mid;
	uint_32 offset_high;
	uint_32 zero;
} IDT64;

extern IDT64 _idt[256];
extern unsigned int isr1;

void initializeIDT(){
	for(unsigned int i = 0; i < 256; ++i){
		_idt[i].zero = 0;
		_idt[i].offset_low = (unsigned short)(((unsigned long) & isr1 & 0x000000000000ffff));
		_idt[i].offset_mid = (unsigned short)(((unsigned long) & isr1 & 0x00000000ffff0000) >> 16);
		_idt[i].offset_high = (unsigned int) (((unsigned long) & isr1 & 0xffffffff00000000) >> 32);
		_idt[i].ist = 0;
		_idt[i].selector = 0x08;
		_idt[i].types_attr = 0x8e;
	}
}
