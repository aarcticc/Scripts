	.file	"telefonbuch.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	leaq	-24576(%rsp), %r11
.LPSRL0:
	subq	$4096, %rsp
	orq	$0, (%rsp)
	cmpq	%r11, %rsp
	jne	.LPSRL0
	subq	$1056, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-25616(%rbp), %rax
	movl	$25600, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movabsq	$3618419310725772331, %rax
	movabsq	$13563782457997617, %rdx
	movq	%rax, -25616(%rbp)
	movq	%rdx, -25608(%rbp)
	movq	$0, -25600(%rbp)
	movq	$0, -25592(%rbp)
	movq	$0, -25584(%rbp)
	movq	$0, -25576(%rbp)
	movq	$0, -25568(%rbp)
	movq	$0, -25560(%rbp)
	movq	$0, -25552(%rbp)
	movq	$0, -25544(%rbp)
	movq	$0, -25536(%rbp)
	movq	$0, -25528(%rbp)
	movq	$0, -25520(%rbp)
	movq	$0, -25512(%rbp)
	movq	$0, -25504(%rbp)
	movq	$0, -25496(%rbp)
	movq	$0, -25488(%rbp)
	movq	$0, -25480(%rbp)
	movq	$0, -25472(%rbp)
	movq	$0, -25464(%rbp)
	movq	$0, -25456(%rbp)
	movq	$0, -25448(%rbp)
	movq	$0, -25440(%rbp)
	movq	$0, -25432(%rbp)
	movq	$0, -25424(%rbp)
	movq	$0, -25416(%rbp)
	movq	$0, -25408(%rbp)
	movq	$0, -25400(%rbp)
	movq	$0, -25392(%rbp)
	movq	$0, -25384(%rbp)
	movq	$0, -25376(%rbp)
	movq	$0, -25368(%rbp)
	movabsq	$3618419310725772331, %rax
	movabsq	$16099264861583665, %rdx
	movq	%rax, -25360(%rbp)
	movq	%rdx, -25352(%rbp)
	movq	$0, -25344(%rbp)
	movq	$0, -25336(%rbp)
	movq	$0, -25328(%rbp)
	movq	$0, -25320(%rbp)
	movq	$0, -25312(%rbp)
	movq	$0, -25304(%rbp)
	movq	$0, -25296(%rbp)
	movq	$0, -25288(%rbp)
	movq	$0, -25280(%rbp)
	movq	$0, -25272(%rbp)
	movq	$0, -25264(%rbp)
	movq	$0, -25256(%rbp)
	movq	$0, -25248(%rbp)
	movq	$0, -25240(%rbp)
	movq	$0, -25232(%rbp)
	movq	$0, -25224(%rbp)
	movq	$0, -25216(%rbp)
	movq	$0, -25208(%rbp)
	movq	$0, -25200(%rbp)
	movq	$0, -25192(%rbp)
	movq	$0, -25184(%rbp)
	movq	$0, -25176(%rbp)
	movq	$0, -25168(%rbp)
	movq	$0, -25160(%rbp)
	movq	$0, -25152(%rbp)
	movq	$0, -25144(%rbp)
	movq	$0, -25136(%rbp)
	movq	$0, -25128(%rbp)
	movq	$0, -25120(%rbp)
	movq	$0, -25112(%rbp)
	movabsq	$3618419310725772331, %rax
	movabsq	$16101468162636081, %rdx
	movq	%rax, -25104(%rbp)
	movq	%rdx, -25096(%rbp)
	movq	$0, -25088(%rbp)
	movq	$0, -25080(%rbp)
	movq	$0, -25072(%rbp)
	movq	$0, -25064(%rbp)
	movq	$0, -25056(%rbp)
	movq	$0, -25048(%rbp)
	movq	$0, -25040(%rbp)
	movq	$0, -25032(%rbp)
	movq	$0, -25024(%rbp)
	movq	$0, -25016(%rbp)
	movq	$0, -25008(%rbp)
	movq	$0, -25000(%rbp)
	movq	$0, -24992(%rbp)
	movq	$0, -24984(%rbp)
	movq	$0, -24976(%rbp)
	movq	$0, -24968(%rbp)
	movq	$0, -24960(%rbp)
	movq	$0, -24952(%rbp)
	movq	$0, -24944(%rbp)
	movq	$0, -24936(%rbp)
	movq	$0, -24928(%rbp)
	movq	$0, -24920(%rbp)
	movq	$0, -24912(%rbp)
	movq	$0, -24904(%rbp)
	movq	$0, -24896(%rbp)
	movq	$0, -24888(%rbp)
	movq	$0, -24880(%rbp)
	movq	$0, -24872(%rbp)
	movq	$0, -24864(%rbp)
	movq	$0, -24856(%rbp)
	movabsq	$3618419310725772331, %rax
	movabsq	$16105866209540401, %rdx
	movq	%rax, -24848(%rbp)
	movq	%rdx, -24840(%rbp)
	movq	$0, -24832(%rbp)
	movq	$0, -24824(%rbp)
	movq	$0, -24816(%rbp)
	movq	$0, -24808(%rbp)
	movq	$0, -24800(%rbp)
	movq	$0, -24792(%rbp)
	movq	$0, -24784(%rbp)
	movq	$0, -24776(%rbp)
	movq	$0, -24768(%rbp)
	movq	$0, -24760(%rbp)
	movq	$0, -24752(%rbp)
	movq	$0, -24744(%rbp)
	movq	$0, -24736(%rbp)
	movq	$0, -24728(%rbp)
	movq	$0, -24720(%rbp)
	movq	$0, -24712(%rbp)
	movq	$0, -24704(%rbp)
	movq	$0, -24696(%rbp)
	movq	$0, -24688(%rbp)
	movq	$0, -24680(%rbp)
	movq	$0, -24672(%rbp)
	movq	$0, -24664(%rbp)
	movq	$0, -24656(%rbp)
	movq	$0, -24648(%rbp)
	movq	$0, -24640(%rbp)
	movq	$0, -24632(%rbp)
	movq	$0, -24624(%rbp)
	movq	$0, -24616(%rbp)
	movq	$0, -24608(%rbp)
	movq	$0, -24600(%rbp)
	movl	$4, -25620(%rbp)
	leaq	-25616(%rbp), %rdx
	movl	-25620(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	start
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	start
	.type	start, @function
start:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$0, %eax
	call	showMenu
	testl	%eax, %eax
	jne	.L5
	movq	-16(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	showPhoneNumbers
	jmp	.L7
.L5:
	movq	-16(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	movl	$0, %eax
	call	addPhoneNumber
.L7:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	start, .-start
	.section	.rodata
.LC0:
	.string	"Telefonnummern:"
.LC1:
	.string	"(%d) %s \n"
	.text
	.globl	showPhoneNumbers
	.type	showPhoneNumbers, @function
showPhoneNumbers:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, -4(%rbp)
	jmp	.L9
.L10:
	movl	-4(%rbp), %eax
	cltq
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -4(%rbp)
.L9:
	cmpl	$9, -4(%rbp)
	jle	.L10
	movq	-32(%rbp), %rdx
	movl	-20(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	start
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	showPhoneNumbers, .-showPhoneNumbers
	.section	.rodata
.LC2:
	.string	"Neue Nummer hinzuf\303\274gen: "
.LC3:
	.string	"%s"
	.text
	.globl	addPhoneNumber
	.type	addPhoneNumber, @function
addPhoneNumber:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$288, %rsp
	movl	%edi, -276(%rbp)
	movq	%rsi, -288(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-272(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	-276(%rbp), %eax
	cltq
	salq	$8, %rax
	movq	%rax, %rdx
	movq	-288(%rbp), %rax
	addq	%rax, %rdx
	leaq	-272(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	strcpy@PLT
	addl	$1, -276(%rbp)
	movq	-288(%rbp), %rdx
	movl	-276(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	start
	nop
	movq	-8(%rbp), %rax
	subq	%fs:40, %rax
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	addPhoneNumber, .-addPhoneNumber
	.section	.rodata
	.align 8
.LC4:
	.string	"###### Herzlich willkommen ######"
.LC5:
	.string	"(0) Telefonnummern anzeigen"
.LC6:
	.string	"(1) Neue Nummer hinzuf\303\274gen"
.LC7:
	.string	" %d"
.LC8:
	.string	"\n"
.LC9:
	.string	"Eingabe ung\303\274ltig!"
	.text
	.globl	showMenu
	.type	showMenu, @function
showMenu:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	leaq	-12(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	-12(%rbp), %eax
	testl	%eax, %eax
	je	.L14
	movl	-12(%rbp), %eax
	cmpl	$1, %eax
	jne	.L15
.L14:
	movl	-12(%rbp), %eax
	jmp	.L17
.L15:
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	call	showMenu
.L17:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L18
	call	__stack_chk_fail@PLT
.L18:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	showMenu, .-showMenu
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
