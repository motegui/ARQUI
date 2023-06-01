global loader
global reset
EXTERN main
EXTERN initializeKernelBinary
EXTERN  getStackBase

loader:
	call initializeKernelBinary	; Set up the kernel binary, and get thet stack address
	mov rsp, rax				; Set up the stack with the returned address
	call main
hang:
	cli
	hlt	; halt machine should kernel return
	jmp hang

;reset
	;call getStackBase
	;mov rsp, rax
	;call main
	;mov rsp, rbp     ;reseteamos el stack para que no se quede sin lugar
    ;mov rax, 0x400000    ;saltamos nuevamente a sample code module
    ;jmp rax
    ;ret



