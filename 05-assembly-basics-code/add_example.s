### Exampls of addition, not likely to run without segfaulting
.section        .text
.globl  main
main:
	 addq %rdx,  %rcx      # rcx = rcx + rdx
	 addl %eax,  %ebx      # ebx = ebx + eax
	 addq $42,   %rdx      # rdx = rdx + 42
	 addl (%rsi),%edi      # edi = edi + *rsi
	 addw %ax,  (%rbx)     # *rbx = *rbx + ax
	 addq $55,  (%rbx)     # *rbx = *rbx + 55

	 addq (%rsi,%rax,4),%rdi    # rdi = rdi+rsi[eax] (int)
