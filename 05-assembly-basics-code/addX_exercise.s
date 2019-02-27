### In-class exercise to study data movement
### Compile with
### > gcc addX_exercise.s
###
### In gdb use the commands
###   gdb> print *($rdx)
### to print the integer pointed to by register rdx.
###   gdb> x/3d $r8
### to print the 3 elements of the stack; d for decimal numbers

.section .data
array:                          # an array
        .int 200
        .int 300
        .int 400

.section        .text
.globl  main
main:

.SETUP:
        movq $15, %rax
        movq $20, %rbx
        movq $25, %rcx
        pushq $100              # push 100 on stack
        movq %rsp,%rdx          # point rdx at location with 100
        leaq array(%rip),%r8
        movq $0,%r9

.EXERCISE:
        addq $1,%rcx            # con + reg
        addq %rbx,%rax          # reg + reg
        ## POS A
        
        addq (%rdx),%rcx        # mem + reg
        addq %rbx,(%rdx)        # reg + mem
        addq $3,(%rdx)          # con + mem
        ## POS B
        
        addl $1,(%r8,%r9,4)     # con + mem
        addl $1,%r9d            # con + reg
        addl %eax,(%r8,%r9,4)   # reg + mem
        addl $1,%r9d            # con + reg
        addl (%r8,%r9,4),%eax   # mem + reg
        ## POS C

.CLEANUP:
        popq %rdx
	movl    $1,%eax
        ret
        
        
