        BITS 64
		section .text
		global asm_strcmp
asm_strcmp:
        cmp	rdi, 0      ; check if rdi is null
        je	out
        cmp	rsi, 0      ; check if rsi is null
        je	out

        xor	rax, rax      ; assume it returns 0 meaning equals

loop:
        mov	BH, [rdi]	; load char to BH
        mov	BL, [rsi]	; load char to BL
        cmp	BH, BL		; compare them
        jne	not_equal	; 

        inc	rdi		; inc rdi to next char
        inc	rsi		; inc rsi to next char
        
	cmp	rdi, 0		; check for null-character
	je	not_equal

	jmp	out		; loop again

not_equal:
	sub	rdi, rsi	; sub to get the difference
	mov	rax, rdi
	jmp	out
out:
        ret			; return rax
