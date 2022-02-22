; main boot sector

[org 0x7c00]

KERNEL_OFFSET equ 0x1000

; store for later
mov [BOOT_DRIVE], dl

; set stack pointers
mov bp, 0x9000
mov sp, bp

; print message
mov bx, MSG_REAL_MODE
call print_string

; load kernel
call load_kernel
; pring message
mov bx, MSG_KERNEL_LOADED
call print_string

; this never returns
jmp switch_to_protected_mode

; we should never reach this
jmp $

%include "util/print_string.asm"
%include "util/print_string_pm.asm"
%include "GDT.asm"
%include "switch_to_pm.asm"
%include "load_kernel.asm"
%include "../kernel/IDT.asm"

[bits 32]

; "global start function"
; called by 'switch_to_protected_mode'
start_protected_mode:
	; print message
	mov ebx, MSG_PROTECTED_MODE
	call print_string_pm
	
	; launch kernel
	call KERNEL_OFFSET
	
	; main loop
	jmp $

; globals
BOOT_DRIVE db 0
MSG_REAL_MODE db "Entered 16-bit real mode", 0x0
MSG_PROTECTED_MODE db "Entered 32-bit protected mode", 0x0
MSG_KERNEL_LOADED db "Loaded kernel", 0x0

; bootsector padding
times 510-($-$$) db 0
dw 0xaa55
