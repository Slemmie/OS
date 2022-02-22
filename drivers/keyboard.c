typedef struct IDT32{
	unsigned short offset_low;
	unsigned short selector;
	unsigned char ist;
	unsigned char types_attr;
	unsigned short offset_mid;
	unsigned int offset_high;
	unsigned int zero;
} IDT32;

extern IDT32 _idt[256];
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
