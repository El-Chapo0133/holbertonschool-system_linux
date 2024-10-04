	BITS 64
		section .text
		global asm_strchr
asm_strchr:
	push rbp
	mov rsp, rbp

	cmp rdi, 0	; check for null
	je out
	cmp rsi, 0	; check for null
	je out

	mov rax, 0	; null by default
	mov BL, BYTE [rsi]
loop:
	mov BH, BYTE [rdi]
	cmp BH, BL
	je found
	
	cmp rdi, 0	; end of string
	je out
	
	inc rdi
	jmp loop

found:
	mov rax, rdi
	jmp out
out:	
	mov rsp, rbp
	pop rbp
	ret
