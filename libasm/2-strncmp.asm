BITS 64
		section .text
		global asm_strncmp
asm_strncmp:
        mov rax, 0
loop:
    mov BL, BYTE [rdi + rdx]
    mov BH, BYTE [rsi + rdx]
	cmp BL, BH
	jnz diff	; when not zero return 1 or -1
	dec rdx		; dec counter
	cmp rdx, 0	; when rdx is at zero
	jz out		; return 0
	jmp loop	; loop again
diff:
        mov rax, 1
        ret
out:
        ret
