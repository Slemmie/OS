[org 0x7e00]

; never return from here
jmp enter_protected_mode

%include "GDT.asm"
%include "./util/print.asm"

; enter 32-bit protected mode
enter_protected_mode:
	call enable_A20

	; disable interrupts
	cli
	
	; load gdt
	lgdt [gdt_descriptor]
	
	; set up 32-bit protected mode
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	; never return from here
	jmp code_segment:start_protected_mode

enable_A20:
	in al, 0x92
	or al, 0x02
	out 0x92, al
	
	ret

[bits 32]

start_protected_mode:
	mov ax, data_segment
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; print yellow X (remove later :))
	mov [0xb8000], byte 'X'
	mov [0xb8001], byte 0x0e
	
	jmp $

times 2048 - ($-$$) db 0
