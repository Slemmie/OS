
idtDescriptor:
	dw 4095 ; size of the IDT:
			; 256 entries with 16 bytes
			; 256*16 = 4096 and the size
	

; isr1 is the interrupt for the keyboard
[extern isr1_handler]
isr1:
	pusha
	call isr1_handler
	popa
	iretd
	GLOBAL isr1

loadIDT:
	lidt[idtDescriptor]
	sti
	ret
	GLOBAL loadIDT
