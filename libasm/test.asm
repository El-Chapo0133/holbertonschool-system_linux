BITS 64
global test

test:
    push    rbp
    mov     rbp, rsp
    push    rcx

    mov rsi, 32    
    mov rdx, 32
    syscall

finish:
    pop     rcx
    mov     rsp, rbp
    pop     rbp
    ret
