; implementation of moving from 16-bit real mode to 32-bit protected mode
; ends with calling the global 'start_protected_mode'
; meaning, 'switch_to_protected_mode' never returns, given 'start_protected_mode' never returns 

[bits 16]

switch_to_protected_mode:
	; switch off interrupts
	cli
	
	; load global descriptor table
	lgdt [gdt_descriptor]
	
	; switch to (32 bit) protected mode
	; update control register
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax
	
	; initialize 32 bit protected mode
	jmp GDT_CODE_SEG:_init_protected_mode

[bits 32]

; initialize registers to work with 32 bit
_init_protected_mode:
	mov ax, GDT_DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; reset stack pointers to right at the top of the free space
	mov ebp, 0x9000
	mov esp, ebp
	
	; finally, properly begin protected mode
	; never return from here
	jmp start_protected_mode
