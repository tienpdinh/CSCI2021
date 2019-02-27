### Demonstrations of the leaX "load effective address" instruction

.section .data
array:                          # an array
        .int 200                # #2048
        .int 300                # #2052
        .int 400                # #2056

.section        .text
.globl  main
main:
	
.SETUP:
        pushq   $15             # stack elements
        pushq   $25             # #1024
        movq    $2,%rcx
        movq    %rsp,%rdx         # top of stack in rdx
        leaq    array(%rip),%rsi  # array in rsi

.EXERCISE:
        movq    8(%rdx),%rax    # rax = *(rdx+1) (long)
	## rax now 25
        leaq    8(%rdx),%rax    # rax = rdx+1    (long)
	## rax now #1032
	movl    (%rsi,%rcx,4),%eax # rax = rsi[rcx]
	## rax now 400
	leaq    (%rsi,%rcx,4),%rax # rax = &(rsi[rcx])
	## rax now #2056
        
        
### Example of using leal to do integer multiplication
	movl    $15,%eax           # eax = 15
	imul    $3,%eax            # eax *= 3
        addl    $1,%eax            # eax += 1
        ## eax now 15*3+1 = 46

	movl    $15,%eax           # eax = 15
        leal    1(%eax,%eax,2),%eax
        ## eax now 15+15*2+1 = 15*3+1 = 46
        ## gcc, you are so clever...
	
	
### Example of leaq to do long multiplication
	movq    $15,%rdi           # rdi = 15
	imulq   $3,%rdi           # rdi *= 3
        addq    $1,%rdi            # rdi += 1
        ## rdi now 15*3+1 = 46

	movq    $15,%rdi           # rdi = 15
        leaq    1(%rdi,%rdi,2),%rdi
        ## rdi now 15+15*2+1 = 15*3+1 = 46
        ## gcc, you are so clever...

        movq     %rdi,%rax
	
.CLEANUP:
        popq    %rdx
        popq    %rdx
        
        ret
