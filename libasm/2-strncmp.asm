		section .text
		global asm_strncmp
asm_strncmp:
        mov rax, 0
        mov rcx, 0
loop:
        test rdx, rdx
        jz out

        mov al, [rdi]
        mov bl, [rsi]

        cmp al, bl
        jne diff

        test al, al
        jz out

        inc rdi
        inc rsi
        dec rdx
        jmp loop
diff:
        mov rax, 1
        ret
out:
        ret