        BITS 64
		section .text
		global asm_strcmp
asm_strcmp:
        cmp rdi, 0      ; check if rdi is null
        je out
        cmp rsi, 0      ; check if rsi is null
        je out

        mov rax, 0      ; assume it returns 0 meaning equals
        cmp rdi, rsi    ; compare 1st arg (rdi) with 2nd arg (rsi)
        jg greater
        je out          ; if equals, jump to out and return
        jl less

        mov rax, 1      ; then assume it returns 1 meaning not equals
        jmp out         ; jump to out and return

greater:
        mov rax, 1
        jmp out
less:
        mov rax, -1
        jmp out
out:
        ret             ; return rax
