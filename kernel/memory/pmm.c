// implements physical memory functoinality

#include "memory.h"

typedef unsigned int _PAG_DIR_T;

_PAG_DIR_T* page_dir = 0;
_PAG_DIR_T  page_dir_location = 0;
_PAG_DIR_T* page_ptr = 0;

void enable_paging() {
	__asm__ volatile ("mov %%cr3, %%eax" : : "a" (page_dir_location));
	__asm__ volatile ("mov %eax, %cr0");
	__asm__ volatile ("or %eax, 0x80000001");
	__asm__ volatile ("mov %cr0, %eax");
}

void map_virt_to_phys(unsigned int virtual, unsigned int physical) {
	unsigned short v_index = virtual >> 22;
	
	for (int i = 0; i < 1024; i++) {
		page_ptr[i] = physical | 3;
		physical += _PM_BLOCK_SIZE;
	}
	
	page_dir[v_index] = ((_PAG_DIR_T) page_ptr) | 3;
	page_ptr = (_PAG_DIR_T*) (((_PAG_DIR_T) page_ptr) + _PM_BLOCK_SIZE);
}

// initialize physical memory
void init_paging() {
	page_dir = (_PAG_DIR_T*) 0x400000;
	page_dir_location = (_PAG_DIR_T) page_dir;
	page_ptr = (_PAG_DIR_T*) 0x404000;
	
	for (int i = 0; i < 1024; i++) {
		page_dir[i] = 2;
	}
	
	map_virt_to_phys(0x0, 0x0);
	map_virt_to_phys(0x400000, 0x400000);
	
	enable_paging();
}
