	.file	"des-example-youtub.c"
	.text
	.globl	val
	.bss
	.align 4
	.type	val, @object
	.size	val, 4
val:
	.zero	4
	.text
	.globl	incriment
	.type	incriment, @function
incriment:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	val(%rip), %eax
	addl	$1, %eax
	movl	%eax, val(%rip)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$99999999, -4(%rbp)
	jle	.L3
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	incriment, .-incriment
	.section	.rodata
.LC0:
	.string	"Valeur value_globale : %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	-8(%rbp), %rax
	movl	$0, %ecx
	movl	$incriment, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	leaq	-16(%rbp), %rax
	movl	$0, %ecx
	movl	$incriment, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	movq	-16(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join
	movl	val(%rip), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240912 (Red Hat 14.2.1-3)"
	.section	.note.GNU-stack,"",@progbits
