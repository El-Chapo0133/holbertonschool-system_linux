		section .text
		global asm_strlen
asm_strlen:
		mov rax, 0
loop:
		cmp BYTE [rdi + rax], 0
		je out
		inc rax
		jump loop
out:
		ret