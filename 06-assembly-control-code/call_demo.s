### Short loop to sum numbers 0 to 100. Compile and disassemble with
### > gcc loop.s
### > objdump -d a.out
### which will show the memory addresses of instructions and branch
### targets.
	
	.section .text
	.global main
sum:
        movq    $0,%rax
        movq    $0,%rcx
        movq    $100,%rdx
LOOP:
        cmpq    %rdx,%rcx
        jg      END
        addq    %rcx,%rax
        incq    %rcx
        jmp     LOOP
END:
        ret
