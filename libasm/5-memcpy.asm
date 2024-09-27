	BITS 64
		section .text
		global memcpy
memcpy:
	push rbp
	mov rsp, rbp

loop:
	cmp rdi, 0
	je out
	mov rsi, rdi

	inc rdi
	inc rsi
	jmp loop

out:
	mov rbp, rsp
	pop rbp
	ret
