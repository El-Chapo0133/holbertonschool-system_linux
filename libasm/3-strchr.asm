	BITS 64
		section .text
		global asm_strchr
asm_strchr:
	push	rbp		; save current base ptr
	mov	rsp, rbp	; establish new base ptr

	cmp	rdi, 0		; check for null
	je	out
	cmp	rsi, 0		; check for null
	je	out

	xor	rax, rax	; null by default
	mov	BL, BYTE [rsi]	; load s2 char to find
loop:
	mov	BH, BYTE [rdi]	; load current char
	cmp	BH, BL		; compare current char with char to find
	je	found		; jump to found when they are equal
	
	cmp	rdi, 0		; check for null-character
	je	out		; if equal jump to out
	
	inc	rdi		; inc char
	jmp	loop		; loop again

found:
	mov	rax, rdi	; move address to rax
	jmp	out
out:	
	mov	rsp, rbp	; restore the stack ptr
	pop	rbp		; restore the base ptr
	ret			; return
