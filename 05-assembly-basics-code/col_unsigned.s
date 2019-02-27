	.file	"col_unsigned.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	movl	$0, %eax
	movl	$10, %edx
	jmp	.L2
.L3:
	shrl	%edx
.L4:
	addl	$1, %eax
.L2:
	cmpl	$1, %edx
	jbe	.L6
	testb	$1, %dl
	je	.L3
	leal	1(%rdx,%rdx,2), %edx
	jmp	.L4
.L6:
	rep ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
