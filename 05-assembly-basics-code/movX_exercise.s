### In-class exercise to study data movement
### Compile with
### > gcc addX_exercise.s
###
### In gdb use the command
###   gdb> x/4dg $rsp
### to print the 4 elements of the stack; d for decimal, g for "giant
### word" of 8 bytes, $rsp for the value of the stack pointer register
.section        .text
.globl  main
main:
.SETUP:
        pushq $5                # a[3] = 5
        pushq $15               # a[2] = 15
        pushq $25               # a[1] = 25
        pushq $35               # a[0] = 35
        movq %rsp, %rcx
        leaq 8(%rsp), %rdx
	movq $0,%rax
	movq $0,%rbx

.EXERCISE:
        movl $16, %eax          # constants to regs
        movl $20, %ebx
        movq $24, %rbx
	## POS A

        movq %rax,%rbx          # reg to reg
	movl %ecx,%eax          # only half of rcx gets moved
	## POS B

        movq $45,(%rdx)         # const to memory
	movq %rbx,(%rcx)        # reg to memory
        movq $55,16(%rdx)       # const to mem+const-offset
	## POS C

        movq $65,(%rcx,%rbx)    # const to mem+reg-offset
	movq $3,%rbx            # const to reg
        movq $75,(%rcx,%rbx,8)  # const to mem+reg*size
	## POS D
        
.CLEANUP:
        popq %rax
        popq %rax
        popq %rax
        popq %rax
        movq $0, %rax
        ret
