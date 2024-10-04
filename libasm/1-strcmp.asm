        BITS 64
		section .text
		global asm_strcmp
asm_strcmp:
        push	rbp
	mov	rbp, rsp

	cmp	rdi, 0		; check if rdi is null
        je	compare
        cmp	rsi, 0		; check if rsi is null
        je	compare

        xor	rax, rax	; assume it returns 0 meaning equals

loop:
        mov	al, [rdi]	; load char to BH
        mov	cl, [rsi]	; load char to BL
        cmp	al, cl		; compare them
        jne	compare		; when not equals return 1 or -1

	cmp	al, 0		; check for null-character
	je	compare

        inc	rdi		; inc rdi to next char
        inc	rsi		; inc rsi to next char

	jmp	loop		; loop again

compare:
	sub	rdi, rsi	; sub to get the difference
	cmp	rdi, 0		; compare to 0
	jg	greater		; if greater return 1
	jl	less		; if less return -1
	je	out		; if equals return 0
greater:
	mov	rax, 1
	jmp	out
less:
	mov	rax, -1
	jmp	out
out:
	mov	rbp, rsp
	pop	rbp
        ret			; return rax
