		section .text
		global asm_strlen
asm_strlen:
		mov rax, 0 ; start a counter to 0
loop:
		; rdi + rax mean we get the caracter, the adress + 1 equals 2nd char
		cmp BYTE [rdi + rax], 0 ; compare 1st arg (rdi) with null-char
		je out ; if cmp is true jump to out and return
		inc rax ; else increment rax
		jmp loop ; jump to loop again
out:
		ret