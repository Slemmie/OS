; print_string (16-bit real mode)

[bits 16]

; store pointer to null terminated string in bx
print_string:
	pusha
	
	; BIOS tele-type output
	mov ah, 0x0e

_print_string_loop:
	; specify which character to print
	mov al, [bx]
	
	; terminate if we reached null-byte
	cmp al, 0
	je _print_string_done
	
	; print the character
	int 0x10
	
	; point to the next character in input string
	add bx, 1
	
	jmp _print_string_loop

_print_string_done:
	popa
	ret
