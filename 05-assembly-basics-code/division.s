### Demonstrate division in assembly. Use in combination with division_main.c
### Compile with
### > gcc division_main.c division.s

        .section        .text
        .global div_small
        .global div_big
	
div_small:  
### division with 32-bit ints
        movl $15, %eax          # set eax to int 15
	cqto                    # extend sign of eax to edx in case it is negative
        ## combined 64-bit register %edx:%eax is 
        ## now 0x00000000 0000000F = 15
	movl $2, %esi           # set esi to 2
        idivl %esi              # divide combined register by 2
	## 15 div 2 = 7 rem 1
        ## %eax == 7, quotient
        ## %edx == 1, remainder
	
        # answer in eax, return
	ret
        
div_big:        
### division with 64-bit longs
        movq $0x0000000300000001, %rax # set rax to long 1
	movq $0, %rdx                  # set rdx to long 0
        ## combined 128-bit register %rdx:%rax is
        ## now 0x00000000 00000000 00000003 00000001 = 12,884,901,889
	movq $13,  %rbx         # set rbx to long 13
        idivq %rbx              # divide combined register by 13
	## 12,884,901,889 div 13 = 991,146,299 rem 2
        ## %rax == 991146299, quotient
        ## %rdx == 2, remainder
	## movq %rdx, %rax
	
	## answer in rax, return
        ret
