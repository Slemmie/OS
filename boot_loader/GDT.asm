; GDT object

gdt_null_descriptor:
	dd 0
	dd 0

gdt_code_segment:
	dw 0xffff    ; limit
	dw 0x0000    ; base (low)
	db 0x00      ; base (med)
	db 10011010b ; access byte
	db 11001111b ; flags | limit
	db 0x00      ; base (hig)

gdt_data_segment:
	dw 0xffff    ; limit
	dw 0x0000    ; base (low)
	db 0x00      ; base (med)
	db 10010010b ; access byte
	db 11001111b ; flags | limit
	db 0x00      ; base (hig)

gdt_end:

gdt_descriptor:
	gdt_size:
		dw gdt_end - gdt_null_descriptor - 1
		dq gdt_null_descriptor

code_segment equ gdt_code_segment - gdt_null_descriptor
data_segment equ gdt_data_segment - gdt_null_descriptor

[bits 32]

edit_gdt:
	mov [gdt_code_segment + 6], byte 10101111b
	
	mov [gdt_data_segment + 6], byte 10101111b
	
	ret

[bits 16]
