BITS 64
		section .text
		global asm_strncmp
asm_strncmp:
	push rbp
	mov rsp, rbp

        mov rax, 0
	; rdi = first string
	; rsi = second string
	; rdx = n char to check
	; mov rdi, QWORD PTR -8 [rbp]
	; mov rsi, QWORD PTR -16[rbp]
	; mov rdx, DWORD PTR -20[rbp]

loop:
        mov BH, BYTE [rdi]    ; store first arg char in BL
        mov BL, BYTE [rsi]    ; store second arg char in BH
        cmp BH, BL	; compare them
        jne diff	; when not zero return the diff
        
	test BH, BH	; check for null-character
	je diff
        test BL, BL	; check for null-character
	je diff
	
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
out:
	mov rbp, rsp
	pop rbp
        ret
