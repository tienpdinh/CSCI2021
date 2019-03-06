	.file	"jmp_tests.c"
	.text
	.globl	func
	.type	func, @function
func:
.LFB13:
	.cfi_startproc
	testl	%esi, %esi
	je	.L6
	movl	$0, %eax
.L2:
	testl	%esi, %esi
	je	.L3
	addl	$30, %eax
.L3:
	testq	%rdx, %rdx
	je	.L4
	addl	$40, %eax
.L4:
	testl	%ecx, %ecx
	js	.L7
.L1:
	rep ret
.L6:
	movl	$20, %eax
	jmp	.L2
.L7:
	addl	$50, %eax
	jmp	.L1
	.cfi_endproc
.LFE13:
	.size	func, .-func
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	movl	$0, %ecx
	movl	$0, %edx
	movl	$3, %esi
	movl	$5, %edi
	call	func
	rep ret
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
