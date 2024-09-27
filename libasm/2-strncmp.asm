	BiTS 64
		section .text
		global asm_strncmp
asm_strncmp:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-24], rdi
        mov     QWORD PTR [rbp-32], rsi
        mov     DWORD PTR [rbp-36], edx
        mov     DWORD PTR [rbp-4], 0
        jmp     .L2
.L6:
        mov     eax, DWORD PTR [rbp-4]
        movsx   rdx, eax
        mov     rax, QWORD PTR [rbp-24]
        add     rax, rdx
        movzx   edx, BYTE PTR [rax]
        mov     eax, DWORD PTR [rbp-4]
        movsx   rcx, eax
        mov     rax, QWORD PTR [rbp-32]
        add     rax, rcx
        movzx   eax, BYTE PTR [rax]
        cmp     dl, al
        jle     .L3
        mov     eax, 1
        jmp     .L4
.L3:
        mov     eax, DWORD PTR [rbp-4]
        movsx   rdx, eax
        mov     rax, QWORD PTR [rbp-24]
        add     rax, rdx
        movzx   edx, BYTE PTR [rax]
        mov     eax, DWORD PTR [rbp-4]
        movsx   rcx, eax
        mov     rax, QWORD PTR [rbp-32]
        add     rax, rcx
        movzx   eax, BYTE PTR [rax]
        cmp     dl, al
        jge     .L5
        mov     eax, -1
        jmp     .L4
.L5:
        add     DWORD PTR [rbp-4], 1
.L2:
        mov     eax, DWORD PTR [rbp-4]
        cmp     eax, DWORD PTR [rbp-36]
        jl      .L6
        mov     eax, 0
.L4:
        pop     rbp
        ret
