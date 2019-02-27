### AT&T syntax for mstore.c translated by gcc
### > gcc -Og -S mstore.c
	.file	"mstore.c"
	.text
	.globl	multstore
	.type	multstore, @function
multstore:
	pushq	%rbx
	movq	%rdx, %rbx
	call	mult2@PLT
	movq	%rax, (%rbx)
	popq	%rbx
	ret
