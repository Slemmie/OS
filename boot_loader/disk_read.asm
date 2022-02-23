PROGRAM_SPACE equ 0x7e00

read_disk:
	mov ah, 0x02
	mov bx, PROGRAM_SPACE
	mov al, 4
	mov dl, [BOOT_DISK]
	mov ch, 0x00
	mov dh, 0x00
	mov cl, 0x02
	
	int 0x13
	
	jc _disk_read_failed
	
	ret

BOOT_DISK:
	db 0

_disk_read_error_string:
	db "Disk Read Failed", 0x0

_disk_read_failed:
	mov bx, _disk_read_error_string
	call print_string
	
	; do not contiunue
	jmp $

%include "./util/print.asm"
