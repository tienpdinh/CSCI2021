### Demonstrates a typical if/else in assembly. Rough C translation is
## if(rbx >= 2){
##   rdx = 10;
## }
## else{
##   rdx = 5;
## }
### Compile and run with
### > gcc jmp_if_else.s
	.section .text
	.global main
main:
        movq    $3,%rbx
	cmpq    $2,%rbx         # compare: rbx - 0
        jl      .LESSTHAN       # goto less than case
        ## if(rbx >= 2){
        movq    $10,%rdx        # greater/equal to 2 case
	## }
	jmp     .AFTER
.LESSTHAN:
	## else{
        movq    $5,%rdx         # less than 2 case
	## }
.AFTER:
        movq    %rdx,%rax
        ret
