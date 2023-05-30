GLOBAL getRegs
GLOBAL getRSP
section .bss
	regs resb 8*18 ;Arquitectura x86-64. Cada registro general tiene un tamaño de 8 bytes.

section .text
getRegs:
	mov [regs], rax       ; Guarda el valor de RAX en regs
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
	mov rax, regs         ; Carga la dirección de regs en RAX
	ret                   ; Retorna el valor en RAX

getRSP:
	mov rax, rsp
	ret
