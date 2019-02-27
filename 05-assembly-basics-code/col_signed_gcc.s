### Annotated output for
### > gcc -Og -S col_signed.c
	.file	"col_simple.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	movl	$0, %eax               # steps is eax, steps = 0
	movl	$10, %edx              # n is edx,     n = 10
	jmp	.L2                    # jump to top of loop
.L7:                                   # ODD CASE
	leal	1(%rdx,%rdx,2), %edx   # n = 1 + n + n*2 = 3*n+1
.L4:                                   # UPDATE
	addl	$1, %eax               # steps++;
.L2:                                   # while(      ){
	cmpl	$1, %edx               #       n > 1
	jle	.L6                    # n <= 1 exit loop
	movl	%edx, %esi             # ??? sequence to do n%2==1
	shrl	$31, %esi              # ??? without division
	leal	(%rdx,%rsi), %ecx      # ??? complex to allow for 
	andl	$1, %ecx               # ??? n being negative in  
	subl	%esi, %ecx             # ??? signed 2's complement
	cmpl	$1, %ecx               # comparison...
	je	.L7                    # jump to ODD CASE
	movl	%edx, %ecx             # EVEN CASE
	shrl	$31, %ecx              # ??? adjustments in case of 
	addl	%ecx, %edx             # ??? negative n values
	sarl	%edx                   # n = n / 2; via right shift
	jmp	.L4                    # jump to UPDATE
.L6:
	rep ret                        # return, eax has steps
	.cfi_endproc                   # "rep ret" for AMD branch prediction bug
.LFE24:
	.size	main, .-main
	.ident	"GCC: (GNU) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
