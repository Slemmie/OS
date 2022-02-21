; GDT object implementation

; GDT
_gdt_start:

; 8 bytes
_gdt_null:
	dd 0x0
	dd 0x0

; 12 bytes
_gdt_code:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

; 12 bytes
_gdt_data:
	dw 0xfff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

_gdt_end:

; GDT descriptor
gdt_descriptor:
	dw _gdt_end - _gdt_start - 1
	dd _gdt_start

; addr segments constants
GDT_CODE_SEG equ _gdt_code - _gdt_start
GDT_DATA_SEG equ _gdt_data - _gdt_start
