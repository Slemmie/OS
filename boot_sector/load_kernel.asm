; code to load an external kernel

[bits 16]

; sets global variable KERNEL_OFFSET
; this assumes the existance of print_string procedure
load_kernel:
	; assumes existance of global variable KERNEL_OFFSET
	mov bx, KERNEL_OFFSET
	mov dh, 15
	mov dl, [BOOT_DRIVE]
	
	call _disk_load
	
	ret

; procedure for loading dh sectors to es:bx from drive dl
_disk_load:
	; store for later
	push dx
	
	mov ah, 0x02 ; BIOS read sector function
	mov al, dh ; number of sectors to read
	mov ch, 0x00 ; cylinder 0
	mov dh, 0x00 ; head 0
	mov cl, 0x02 ; read from second sector (1-indexed)
	
	; BIOS interrupt
	int 0x13
	
	; carry bit will be set for errors
	jc disk_error
	
	; restore dx
	pop dx
	
	; display error if sectors read != sectors wanted read
	cmp dh, al
	jne disk_error
	
	ret

; this assumes the existance of print_string procedure
disk_error:
	mov bx, DISK_ERROR_MSG
	call print_string
	jmp $

; error message
DISK_ERROR_MSG db "Failed to read disk", 0x0
