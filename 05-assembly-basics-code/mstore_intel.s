### Intel assembly syntax for mstore.c translated by gcc
### > gcc -Og -S -masm=intel mstore.c
	.file	"mstore.c"
	.intel_syntax noprefix
	.text
	.globl	multstore
	.type	multstore, @function
multstore:
	push	rbx
	mov	rbx, rdx
	call	mult2@PLT
	mov	QWORD PTR [rbx], rax
	pop	rbx
	ret

