		section .text
		global asm_strcmp
asm_strcmp:
        mov rax, 0 ; assume it returns 0 meaning equals
        cmp rdi, rsi ; compare 1st arg (rdi) with 2nd arg (rsi)
        je out ; if equals, jump to out and return

        mov rax, 1 ; then assume it returns 1 meaning not equals
        jmp out ; jump to out and return

out:
        ret ; return rax