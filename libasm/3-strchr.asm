	BITS 64
		section .text
		global strchr
strchr:
	push rbp
	mov rsp, rbp

	cmp rdi, 0	; check for null
	je out
	cmp rsi, 0	; check for null
	je out

	mov rax, 0	; null by default
loop:
	mov BH, BYTE [rdi]
	mov BL, BYTE [rsi]
	cmp BH, BL
	je found
	
	inc rdi
	cmp rdi, 0	; end of string
	je out
	jmp loop

found:
	mov rax, rdi
	jmp out
out:	
	mov rbp, rsp
	pop rbp
	ret
