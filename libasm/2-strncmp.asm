BITS 64
		section .text
		global asm_strncmp
asm_strncmp:
	push	rbp		; save current base ptr
	mov	rbp, rsp	; establish a new base ptr
	xor	rax, rax	; clear rax to ensure clean output
	push	rcx		; initialize a counter
	; rdi = first string
	; rsi = second string
	; rdx = n char to check

loop:
        movzx rax, BYTE [rdi]    ; store first arg char in BL
        movzx rcx, BYTE [rsi]    ; store second arg char in BH
        cmp al, cl	; compare them
        jne diff	; when not zero return the diff

	test al, al	; check for null-character
	je equal

	inc rdi		; inc to next char
	inc rsi		; inc to next char
	dec rdx		; dec counter
	jnz loop	; as long as rdx is not 0 loop again

	; here means it's the end of the counter, so result=0
	xor rax, rax
	jmp out
diff:
	sub rax, rcx
        jmp out
equal:
	xor rax, rax
out:
	pop	rcx
	mov	rbp, rsp	; restore the stack ptr
	pop	rbp		; restore the base ptr
        ret			; return
