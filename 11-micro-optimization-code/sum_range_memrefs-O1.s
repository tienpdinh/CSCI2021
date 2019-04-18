### Compiled with -O1 - do some optimizations
	.file	"sum_range.c"
	.text
	.globl	sum_range1
	.type	sum_range1, @function
sum_range1:
.LFB24:
	.cfi_startproc
	movl	$0, (%rdx)      # write to memory but..
	cmpl	%esi, %edi
	jge	.L1
	movl	$0, %eax        # move 0 to register
.L3:
	addl	%edi, %eax      # add to register
	addl	$1, %edi        # no memory ref...
	cmpl	%edi, %esi
	jne	.L3
	movl	%eax, (%rdx)    # write at end
.L1:
	rep ret
	.cfi_endproc
.LFE24:
	.size	sum_range1, .-sum_range1
	.globl	sum_range2
	.type	sum_range2, @function
sum_range2:
.LFB25:
	.cfi_startproc
	cmpl	%esi, %edi
	jge	.L8
	movl	$0, %eax
.L7:
	addl	%edi, %eax
	addl	$1, %edi
	cmpl	%edi, %esi
	jne	.L7
.L6:
	movl	%eax, (%rdx)
	ret
.L8:
	movl	$0, %eax
	jmp	.L6
	.cfi_endproc
.LFE25:
	.size	sum_range2, .-sum_range2
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"usage: %s <start> <stop> \n"
.LC2:
	.string	"sum_range1: %.4e secs\n"
.LC3:
	.string	"sum_range2: %.4e secs\n"
.LC4:
	.string	"sum_range.c"
.LC5:
	.string	"sum1 == sum2"
	.text
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	%rsi, %rbx
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	cmpl	$2, %edi
	jle	.L16
	movq	8(%rsi), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol@PLT
	movq	%rax, %rbp
	movq	16(%rbx), %rdi
	movl	$10, %edx
	movl	$0, %esi
	call	strtol@PLT
	movq	%rax, %rbx
	call	clock@PLT
	movq	%rax, %r12
	movq	%rsp, %rdx
	movl	%ebx, %esi
	movl	%ebp, %edi
	call	sum_range1
	call	clock@PLT
	subq	%r12, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC1(%rip), %xmm0
	leaq	.LC2(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	call	clock@PLT
	movq	%rax, %r12
	leaq	4(%rsp), %rdx
	movl	%ebx, %esi
	movl	%ebp, %edi
	call	sum_range2
	call	clock@PLT
	subq	%r12, %rax
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rax, %xmm0
	divsd	.LC1(%rip), %xmm0
	leaq	.LC3(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	4(%rsp), %eax
	cmpl	%eax, (%rsp)
	jne	.L17
	movl	$0, %eax
.L10:
	movq	8(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L18
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L16:
	.cfi_restore_state
	movq	(%rsi), %rsi
	leaq	.LC0(%rip), %rdi
	call	printf@PLT
	movl	$-1, %eax
	jmp	.L10
.L17:
	leaq	__PRETTY_FUNCTION__.3201(%rip), %rcx
	movl	$55, %edx
	leaq	.LC4(%rip), %rsi
	leaq	.LC5(%rip), %rdi
	call	__assert_fail@PLT
.L18:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.3201, @object
	.size	__PRETTY_FUNCTION__.3201, 5
__PRETTY_FUNCTION__.3201:
	.string	"main"
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 7.2.1 20171128"
	.section	.note.GNU-stack,"",@progbits
