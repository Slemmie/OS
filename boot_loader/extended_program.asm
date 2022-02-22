[org 0x7e00]

mov bx, ExtendedSpaceSuccess
call PrintString

jmp $

%include "./util/print.asm"

ExtendedSpaceSuccess:
	db "Entered extended space successfully", 0

times 2048 - ($-$$) db 0
