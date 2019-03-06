### Demonstrate several calls to sum_range function. Uses callee save
### registers to preserve values across function calls which
### necessitates restoring those callee save regs at the end of main
### function.

.text
.globl  sum_range
sum_range:
        movl    $0, %eax
        jmp     .TOP
.BODY:
        addl    %edi, %eax
        addl    $1, %edi
.TOP:
        cmpl    %esi, %edi
        jle     .BODY
        rep ret
        
.globl  main
main:
	## %rsp at 8 byte offset due to previous %rip
        pushq   %rbp            # save callee-save registers
        pushq   %rbx            # use these to preserve answers 
	                        # across func calls
	
        subq    $8, %rsp        # align stack for func calls
        
        movl    $1, %edi        # set up params
        movl    $5, %esi        
        call    sum_range       # call function
        movl    %eax, %ebx      # save answer in callee save reg
        
        movl    $10, %edi       # set up params
        movl    $15, %esi       
        call    sum_range       # call function
        movl    %eax, %ebp      # save answer in callee save reg
        
        movl    $20, %edi       # set up params
        movl    $25, %esi       
        call    sum_range       # call function
        
        addl    %eax,%ebp       # total sums
        addl    %ebx,%ebp       # ebp = tot
        
        leaq    .FMT(%rip),%rdi # arg 1 : format string
        movl    %ebp,%esi       # arg 2 : tot
        movl    $0, %eax        # special rule for printf
        call    printf@PLT      # trick for dynamic linking
        ## call    printf          # requires 'gcc -static' to compile 

	## addq    $8,%rsp         # remove stack offset
        popq    %rbx            # restore registers
        popq    %rbp
        ret

.data
.FMT: 
        .string "total: %d\n"
        

        
