; print_string (32-bit protected mode)

[bits 32]

VIDEO_MEMORY_ADDR equ 0xb8000
TEXT_FORMAT_WHITE_FG_BLACK_BG equ 0x0f

; store pointer to null terminated string in ebx
print_string_pm:
	pusha
	
	; use edx to point to vid-mem
	mov edx, VIDEO_MEMORY_ADDR

_print_string_loop_pm:
	; prepare ax register
	mov al, [ebx]
	mov ah, TEXT_FORMAT_WHITE_FG_BLACK_BG
	
	; terminate if we reached null-byte
	cmp al, 0
	je _print_string_done_pm
	
	mov [edx], ax
	
	; point to the next character in input string
	inc ebx
	; move to next index in vid-mem
	add edx, 2
	
	jmp _print_string_loop_pm

_print_string_done_pm:
	popa
	ret
