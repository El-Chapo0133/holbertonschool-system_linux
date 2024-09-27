	BITS 64
		section .text
		global memcpy
memcpy:
	push rbp
	mov rsp, rbp
	
	cmp rdx, 0	; check for null
	je out

	mov rcx, 0
loop:
	cmp rdi + rcx, 0
	je out
	mov rsi + rcx, rdi + rcx

	inc rcx
	jmp loop

out:
	mov rbp, rsp
	pop rbp
	ret
