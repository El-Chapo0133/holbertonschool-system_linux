BITS 64
		section .text
		global asm_strncmp
asm_strncmp:
	push rbp
	mov rbp, rsp

        mov rax, 0

	cmp rdx, 0
	je out
loop:
        mov BH, BYTE [rdi]    ; store first arg char in BL
        mov BL, BYTE [rsi]    ; store second arg char in BH
        cmp BH, BL	; compare them
        jne diff	; when not zero return 1 or -1
        test BH, BH	; check for null-character
	je end_of_str
	inc rdi		; inc to next char
	inc rsi		; inc to next char
        dec rdx		; dec counter
	jnz loop	; as long as rdx is not 0 loop again

	; here means it's the end of the counter, so result=0
	mov rax, 0
	jmp out
diff:
	sub rdi, rsi
	mov rax, rdi
        jmp out
end_of_str:
	xor rdx, rdx
out:
	mov rsp, rbp
	pop rsp
        ret
