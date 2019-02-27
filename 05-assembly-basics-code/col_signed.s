	.file	"col_signed.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	movl	$0, %eax
	movl	$10, %edx
	jmp	.L2
.L7:
	leal	1(%rdx,%rdx,2), %edx
.L4:
	addl	$1, %eax
.L2:
	cmpl	$1, %edx
	jle	.L6
	movl	%edx, %esi
	shrl	$31, %esi
	leal	(%rdx,%rsi), %ecx
	andl	$1, %ecx
	subl	%esi, %ecx
	cmpl	$1, %ecx
	je	.L7
	movl	%edx, %ecx
	shrl	$31, %ecx
	addl	%ecx, %edx
	sarl	%edx
	jmp	.L4
.L6:
	rep ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.1 20171128"
	.section	.note.GNU-stack,"",@progbits
