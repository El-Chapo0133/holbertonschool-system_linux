	BITS 64
		section .text
		global asm_strchr
asm_strchr:
	push	rbp		; save current base ptr
	mov	rbp, rsp	; establish new base ptr
	xor	rax, rax	; null by default

	cmp	rdi, 0		; check for null
	je	out
	cmp	rsi, 0		; check for null
	je	out

loop:
	mov	al, BYTE [rdi]	; load current char
	; sil is the lowest 8 bits of rsi
	cmp	al, sil		; compare current char with char to find
	je	found		; jump to found when they are equal

	cmp	al, 0		; check for null-character
	je	out		; if equal jump to out

	inc	rdi		; inc char
	jmp	loop		; loop again

found:
	mov	rax, rdi	; move address to rax
	jmp	out
out:	
	mov	rbp, rsp	; restore the stack ptr
	pop	rbp		; restore the base ptr
	ret			; return
