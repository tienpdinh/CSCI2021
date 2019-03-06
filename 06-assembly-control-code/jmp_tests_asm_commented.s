### Compile and run with
### > gcc jmp_test_asm.s

### Demonstrates a typical if/else in assembly.
### Rough C translation is
### if(edi == 0){
###   eax += 20;
### }
### if(esi){
###   eax += 30;
### }
### if(edx != NULL){
###   eax += 40;
### }
### if(ecx < 0){
###   eax += 50;
### }
        .section .text
        .global main
main:
        movl    $0,%eax         # eax is 0
        
        movl    $5,%edi         # set initial vals 
        movl    $3,%esi         # for registers to
        movl    $0,%edx         # use in tests
        movl    $-4,%ecx
        
	## eax=0, edi=5, esi=3, edx=NULL, ecx=-4
        testl   %edi,%edi       # any bits set?
        jnz     .NONZERO        # jump on !ZF (zero flag), same as jne
        ## if(edi == 0){        
        addl    $20,%eax
        ## }
.NONZERO:
        testl   %esi,%esi       # any bits set?
        jz      .FALSEY         # jump on ZF same as je
        ## if(esi){             
        addl    $30,%eax
        ## }
.FALSEY:
        testl   %edx,%edx       # any bits set
        je      .ISNULL         # same as jz: jump on ZF 
        ## if(edx != NULL){   
        addl    $40,%eax
        ## }
.ISNULL:
        testl   %ecx,%ecx       # any bits set, sign flag set on test
        jns      .NEGATIVE      # jump on !SF (not sign flag/pos)
        ## if(ecx < 0){
        addl    $50,%eax
        ## }
.NEGATIVE:
        ## eax is return value
        ret
