; detecting some cpu 64-bit compatibilities

detect_CPUID:
	pushfd
	pop eax
	
	mov ecx, eax
	
	xor eax, 1 << 21
	
	push eax
	popfd
	
	pushfd
	pop eax
	
	push ecx
	popfd
	
	xor eax, ecx
	jz _no_CPUID
	
	ret

detect_long_mode_support:
	mov eax, 0x80000001
	cpuid
	test edx, 1 << 29
	jz _no_long_mode
	
	ret

; support for long mode does not exist...
_no_long_mode:
	hlt

; support for CPUID does not exist...
_no_CPUID:
	hlt
