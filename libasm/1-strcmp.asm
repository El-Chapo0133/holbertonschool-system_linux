        BITS 64
		section .text
		global asm_strcmp
asm_strcmp:
        cmp rdi, 0      ; check if rdi is null
        je out
        cmp rsi, 0      ; check if rsi is null
        je out

        mov rax, 0      ; assume it returns 0 meaning equals

loop:
        mov BL, [rsi]
        mov BH, [rdi]
        cmp rsi, rdi
        jne not_equal

        inc rdi
        inc rsi
        jmp out

not_equal:
        sub rdi, rsi
        cmp rdi, 0
        jg greater
        jl less
greater:
        mov rax, 1
        ret
less:
        mov rax, -1
        ret
out:
        ret             ; return rax
