; main boot loader

; read disk ->
; go 32-bit mode ->
; go 64-bit mode ->
; launch kernel

[org 0x7c00]

mov [BOOT_DISK], dl

mov bp, 0x7c00
mov sp, bp

call read_disk

jmp PROGRAM_SPACE

%include "disk_read.asm"

times 510 - ($-$$) db 0
dw 0xaa55

