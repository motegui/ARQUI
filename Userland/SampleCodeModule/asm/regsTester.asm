global testRegs

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

testRegs:
    pushState
    mov r10, 10
    mov r9, 5
    mov rax, 0000000000000001h
    mov r8, 1000000000

loop:
    sub r8, 1     ; Resta 1 del contador r8
    cmp r8, 0
    jne loop      ; Salta a 'loop' si r8 no es igual a cero

    popState

    ret