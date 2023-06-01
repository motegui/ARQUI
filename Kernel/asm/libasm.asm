GLOBAL cpuVendor
GLOBAL kbFlag

GLOBAL getHours
GLOBAL getMinutes
GLOBAL getSeconds
GLOBAL regs

section .text

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;agregado
;kbFlag:
;        push rbp
 ;       mov rbp, rsp
;		mov rax,0
;loop:
	;in al,0x64
    ;mov cl,al
   ; and al,0x01
  ;  je loop
 ;   in al,0x60
;	mov rsp, rbp
 ;   pop rbp
;    ret

kbFlag:
        push rbp
        mov rbp, rsp
		push rax
        push rcx
		mov rax,0

loop:
	in al,0x64
    mov cl,al
    and al,0x01
    je loop

    in al,0x60
    cmp al,1Dh
    je loadRegisters

	mov rsp, rbp
    pop rbp
    ret

loadRegisters
	pop rax
	pop rcx
    mov [regs], rax      ; Guarda el valor de RAX en regs
	mov [regs+8], rbx     ; Guarda el valor de RBX en regs+8
	mov [regs+8*2], rcx   ; Guarda el valor de RCX en regs+16
	mov [regs+8*3], rdx   ; Guarda el valor de RDX en regs+24
	mov [regs+8*4], rbp   ; Guarda el valor de RBP en regs+32
	mov [regs+8*5], rdi   ; Guarda el valor de RDI en regs+40
	mov [regs+8*6], rsi   ; Guarda el valor de RSI en regs+48
	mov [regs+8*7], r8    ; Guarda el valor de R8 en regs+56
	mov [regs+8*8], r9    ; Guarda el valor de R9 en regs+64
	mov [regs+8*9], r10   ; Guarda el valor de R10 en regs+72
	mov [regs+8*10], r11  ; Guarda el valor de R11 en regs+80
	mov [regs+8*11], r12  ; Guarda el valor de R12 en regs+88
	mov [regs+8*12], r13  ; Guarda el valor de R13 en regs+96
	mov [regs+8*13], r14  ; Guarda el valor de R14 en regs+104
	mov [regs+8*14], r15  ; Guarda el valor de R15 en regs+112
	mov al,1Dh
    mov rsp, rbp
    pop rbp
    ret 
    

getSeconds:
    push rbp
    mov rbp,rsp
    mov al, 0
    out 70h, al
    in al, 71h
    mov rsp, rbp
    pop rbp
    ret
getMinutes:
    push rbp
    mov rbp,rsp
    mov al, 2
    out 70h, al
    in al, 71h
    mov rsp, rbp
    pop rbp
    ret
getHours:
        push rbp
        mov rbp, rsp
        mov rax,0
        mov al, 4
        out 70h, al
        in al, 71h
        mov rsp, rbp
        pop rbp
        ret

section .bss
regs resb 8*18	 ;Arquitectura x86-64. Cada registro general tiene un tamaño de 8 bytes.

