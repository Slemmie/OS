; main boot sector

[org 0x7c00]

; set stack pointers
mov bp, 0x9000
mov sp, bp

; print message
mov bx, MSG_REAL_MODE
call print_string

; this never returns
jmp switch_to_protected_mode

; we should never reach this
jmp $

%include "util/print_string.asm"
%include "util/print_string_pm.asm"
%include "GDT.asm"
%include "switch_to_pm.asm"

; "global start function"
; called by 'switch_to_protected_mode'
start_protected_mode:
	; print message
	mov ebx, MSG_PROTECTED_MODE
	call print_string_pm
	
	; main loop
	jmp $

; globals
MSG_REAL_MODE db "Entered 16-bit real mode", 0x0
MSG_PROTECTED_MODE db "Entered 32-bit protected mode", 0x0

; bootsector padding
times 510-($-$$) db 0
dw 0xaa55
