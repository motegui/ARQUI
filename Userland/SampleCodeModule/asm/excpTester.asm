GLOBAL divzerotester
GLOBAL opcodetester

divzerotester:

    mov rax, 0
	div rax
	ret

opcodetester:

    ud2         ;test invalid opcode
    ret