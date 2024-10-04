	BITS 64
		section .text
		global strstr
strstr:
	push	rbp
	mov	rbp, rsp
	xor	rax, rax

	cmp rdi, 0	; check for null
	je out
	cmp rsi, 0	; check for null
	je out

	mov rdx, 0	; setup 1st counter
	mov rcx, 0	; setup 2nd counter

loop:
	mov al, BYTE [rdi + rdx]
	mov bl, BYTE [rsi + rcx]
	cmp al, bl	; compare both char
	je next_step	; if equal inc counter and check for null
	jne undo_step	; if not reset the counter

	inc rdx		; inc 1st counter

	cmp rdi + rdx, 0; check for end of rdi
	je out
	jmp loop

next_step:
	inc rcx			; inc 2nd counter
	cmp rsi + rcx, 0	; check for end of rsi, meaning full string matches
	je found
undo_step:
	mov rcx, 0
found:
	mov rax, rdi + rdx - rcx; mov first char of occurence in rdi
	jmp out
out:
	mov	rbp, rsp
	pop	rbp
	ret
