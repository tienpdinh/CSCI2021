# Demonstrates how 32-bit instructions like addl automatically zero out
# the upper bits of the 64-bit registers while 16-bit and lower 
# instructions do not.

.data
.FMT: 
        .string "val: %08x %016lx\n" # format string for printing int/long regs

.text
.globl  main
main:
	
        ## Demonstrate how 32-bit ops overwrite upper bits
        ## in 64-bit registers
        movq    $-1,%rsi        # rdi all 1's
        addl    $8,%esi         # 32-bit add, zeros upper bits of 64-bit reg
	movq    %rsi,%rdx       # copy rdi to rsi
        leaq    .FMT(%rip),%rdi # arg 1 : format string
        movl    $0, %eax        # special rule for printf
        call    printf@PLT      # print values, @PLT enables dynamic linking
	## OUTPUT:
	## val: 00000007 0000000000000007

	## 32-bit subtraction: also 0's upper 32 bits
        movq    $0,%rsi         # rdi all 0's
        subl    $3,%esi         # 32-bit subtract, zeros upper bits of 64-bit reg
	movq    %rsi,%rdx       # copy rdi to rsi
        leaq    .FMT(%rip),%rdi # arg 1 : format string
        movl    $0, %eax        # special rule for printf
        call    printf@PLT      # print values, @PLT enables dynamic linking
	## OUTPUT:
        ## val: fffffffd 00000000fffffffd

        ## Demonstrate how 16-bit ops DO NOT overwrite upper bits
        ## in 64-bit registers
        movq    $-1,%rsi        # rdi all 1's
        addw    $8,%si          # 16-bit add, DOES NOT overwrite upper bits
	movq    %rsi,%rdx       # copy rdi to rsi
        leaq    .FMT(%rip),%rdi # arg 1 : format string
        movl    $0, %eax        # special rule for printf
        call    printf@PLT      # print values, @PLT enables dynamic linking
	## OUTPUT:
        ## val: ffff0007 ffffffffffff0007
	
        movl    $0,%eax
        ret
