[org 0x7e00]

; prepare 32-bit mode
; then prepare 64-bit mode
; never return from here
jmp enter_protected_mode

%include "GDT.asm"

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
	
	; move to 32-bit mode
	; never return from here
	jmp code_segment:start_protected_mode

enable_A20:
	in al, 0x92
	or al, 0x02
	out 0x92, al
	
	ret

[bits 32]

%include "CPUID.asm"
%include "paging.asm"

; main 32-bit section
start_protected_mode:
	mov ax, data_segment
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; get ready for moving to 64-bit mode
	
	call detect_CPUID
	
	call detect_long_mode_support
	
	call set_up_identity_paging
	
	call edit_gdt
	
	; move to 64 bit mode
	; never return from here
	jmp code_segment:start_64bit

[bits 64]

; main 64-bit section
start_64bit:
	; make screen blue :)
	; remove later
	mov edi, 0xb8000
	mov rax, 0x1f201f201f201f20
	mov ecx, 25 * 80 / 4
	rep stosq
	
	; jump infinetely
	jmp $

times 2048 - ($-$$) db 0
