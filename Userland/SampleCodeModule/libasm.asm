GLOBAL syswrite
GLOBAL sysread
GLOBAL sysrtc
GLOBAL sysmem
GLOBAL sysregs
GLOBAL systemp
section .text

syswrite: 
	push rbp
	mov rbp, rsp

	push rbx
	push rdi
	push rsi

	mov rax, rdi	;shifteamos los registros para mandar la info en el orden que queremos
	mov rbx, rsi
	
	mov rdi, 4
	mov rsi, rax
	mov rdx, rbx
	int 80h

	pop rsi
	pop rdi
	pop rbx

	mov rsp, rbp
	pop rbp
	ret


sysread: 
	push rbp
	mov rbp, rsp

	push rbx
	push rdi
	push rsi

	mov rax, rdi	;shifteamos los registros para mandar la info en el orden que queremos
	mov rbx, rsi
	
	mov rdi, 3
	mov rsi, rax
	mov rdx, rbx
	int 80h

	pop rsi
	pop rdi
	pop rbx

	mov rsp, rbp
	pop rbp
	ret

sysrtc:
	push rbp
    mov rbp, rsp
	push rdi
	push rsi

    mov rsi, rdi
	mov rdi, 1
    int 80h
	
	pop rsi
	pop rdi

    mov rsp, rbp
    pop rbp
    ret

sysmem:
	push rbp
    mov rbp, rsp
	
	push rbx
	push rdi
	push rsi
	
	mov rax, rdi	;shifteamos los registros para mandar la info en el orden que queremos
	mov rbx, rsi

	mov rdi, 2
	mov rsi, rax
	mov rdx, rbx
	int 80h

	pop rsi
	pop rdi
	pop rbx

	mov rsp, rbp
	pop rbp
	ret

sysregs:
	push rbp
    mov rbp, rsp
	
	push rdi
	push rsi
	
	mov rax, rdi	;shifteamos los registros para mandar la info en el orden que queremos

	mov rdi, 5
	mov rsi, rax
	int 80h

	pop rsi
	pop rdi

	mov rsp, rbp
	pop rbp
	ret
