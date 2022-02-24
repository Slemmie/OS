OUTPUT_FORMAT(binary)

ENTRY (_start)

INPUT (
	boot_loader/extended_program.o
	kernel/kernel.o
	kernel/port_io.o
	kernel/util/algorithm.o
	kernel/vidmem/vidmem.o
	kernel/drivers/IDT.o
)

OUTPUT (
	kernel/kernel.bin
)

SECTIONS {
	. = 0x8000;
	
	.text : ALIGN(0x1000) {
		*(.text)
	}
	
	.idt BLOCK(0x1000) : ALIGN(0x1000) {
		_idt = .;
		. = . + 0x1000;
	}
	
	.data : ALIGN(0x1000) {
		*(.data)
	}
	
	.rodata : ALIGN(0x1000) {
		*(.rodata)
	}
	
	.bss : ALIGN(0x1000) {
		*(COMMON)
		*(.bss)
	}
}
