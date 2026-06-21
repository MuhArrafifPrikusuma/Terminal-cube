	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$416, %rsp
	movl	%edi, -404(%rbp)
	movq	%rsi, -416(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	call	initscr@PLT
	call	cbreak@PLT
	call	noecho@PLT
	movq	stdscr(%rip), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	nodelay@PLT
	movl	$0, %edi
	call	curs_set@PLT
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -384(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -376(%rbp)
	movl	$3, -356(%rbp)
	movl	$5, -360(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -368(%rbp)
	movb	$0, -352(%rbp)
	movb	$1, -351(%rbp)
	movsd	-384(%rbp), %xmm0
	cvttsd2sil	%xmm0, %ecx
	movsd	-376(%rbp), %xmm0
	cvttsd2sil	%xmm0, %edx
	movl	-360(%rbp), %esi
	movl	-356(%rbp), %eax
	movl	%eax, %edi
	call	newwin@PLT
	movq	%rax, -344(%rbp)
	leaq	-336(%rbp), %rax
	movl	$320, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset@PLT
	jmp	.L2
.L3:
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wgetch@PLT
	movl	%eax, -388(%rbp)
	movl	-388(%rbp), %edx
	leaq	-384(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	updatePlayer@PLT
	leaq	-336(%rbp), %rdx
	leaq	-384(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	handleCollision@PLT
	leaq	-336(%rbp), %rax
	movq	%rax, %rdi
	call	handleObj@PLT
	leaq	-336(%rbp), %rdx
	leaq	-384(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	render@PLT
	movl	$10667, %edi
	call	usleep@PLT
.L2:
	movzbl	-352(%rbp), %eax
	xorl	$1, %eax
	testb	%al, %al
	jne	.L3
	movq	stdscr(%rip), %rax
	movq	%rax, %rdi
	call	wgetch@PLT
	call	endwin@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1076101120
	.align 8
.LC1:
	.long	0
	.long	1077149696
	.ident	"GCC: (GNU) 16.1.1 20260430"
	.section	.note.GNU-stack,"",@progbits
