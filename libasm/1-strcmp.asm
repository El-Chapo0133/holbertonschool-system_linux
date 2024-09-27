		section .text
		global asm_strcmp
asm_cmpstr:
        mov rax, 0

        cmp rdi, rsi
        je out

        mov rax, 1
        jmp out

out:
        ret