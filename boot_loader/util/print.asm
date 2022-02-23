; print a null-terminated string (16-bit mode)
; move string ptr to bx register before calling

print_string:
	push ax
	push bx
	
	mov ah, 0x0e
	
	.loop:
		; are we done?
		cmp [bx], byte 0
		je .exit
		
		; print character
		mov al, [bx]
		int 0x10
		
		; go again
		inc bx
		jmp .loop
	
	.exit:
		pop bx
		pop ax
		ret
