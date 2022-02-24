
[extern _idt]

idtDescriptor:
	dw 4095 ; size of the IDT:
	        ; 256 entries with 16 bytes
	        ; 256 * 16 = 4096 and the size
	dq _idt

%include "util/push_pop_all_64.asm"

; isr1 is the interrupt for the keyboard
[extern _isr1_handler]

isr1:
	PUSH_ALL_64
	call _isr1_handler
	POP_ALL_64
	iretq
	GLOBAL isr1

load_IDT:
	lidt[idtDescriptor]
	sti
	ret
	GLOBAL load_IDT
