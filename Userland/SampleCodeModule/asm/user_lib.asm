GLOBAL int_80

int_80:
    push rbp
    mov rbp, rsp
    int 80
    mov rsp, rbp
    pop rbp
    ret