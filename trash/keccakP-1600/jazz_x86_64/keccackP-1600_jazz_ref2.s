	.att_syntax
	.text
	.p2align	5
	.globl	__keccak1600_ref
	.globl	_keccak1600_ref
__keccak1600_ref:
_keccak1600_ref:
	movq	%rsp, %rax
	leaq	-496(%rsp), %rsp
	andq	$-8, %rsp
	movq	%rbx, 448(%rsp)
	movq	%rbp, 456(%rsp)
	movq	%r12, 464(%rsp)
	movq	%r13, 472(%rsp)
	movq	%r14, 480(%rsp)
	movq	%rax, 488(%rsp)
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movb	%r8b, 440(%rsp)
	xorq	%rax, %rax
	movq	%rax, 40(%rsp)
	movq	%rax, 48(%rsp)
	movq	%rax, 56(%rsp)
	movq	%rax, 64(%rsp)
	movq	%rax, 72(%rsp)
	movq	%rax, 80(%rsp)
	movq	%rax, 88(%rsp)
	movq	%rax, 96(%rsp)
	movq	%rax, 104(%rsp)
	movq	%rax, 112(%rsp)
	movq	%rax, 120(%rsp)
	movq	%rax, 128(%rsp)
	movq	%rax, 136(%rsp)
	movq	%rax, 144(%rsp)
	movq	%rax, 152(%rsp)
	movq	%rax, 160(%rsp)
	movq	%rax, 168(%rsp)
	movq	%rax, 176(%rsp)
	movq	%rax, 184(%rsp)
	movq	%rax, 192(%rsp)
	movq	%rax, 200(%rsp)
	movq	%rax, 208(%rsp)
	movq	%rax, 216(%rsp)
	movq	%rax, 224(%rsp)
	movq	%rax, 232(%rsp)
	jmp 	L_keccak1600_ref$17
L_keccak1600_ref$18:
	movq	%r9, %rax
	shrq	$3, %rax
	movq	$0, %rsi
	jmp 	L_keccak1600_ref$21
L_keccak1600_ref$22:
	movq	(%rdx,%rsi,8), %rdi
	xorq	%rdi, 40(%rsp,%rsi,8)
	incq	%rsi
L_keccak1600_ref$21:
	cmpq	%rax, %rsi
	jb  	L_keccak1600_ref$22
	addq	%r9, %rdx
	subq	%r9, %rcx
	movq	%rdx, 16(%rsp)
	movq	%rcx, 24(%rsp)
	movq	%r9, 32(%rsp)
	leaq	glob_data + 0(%rip), %rax
	movq	$0, %rcx
	jmp 	L_keccak1600_ref$19
L_keccak1600_ref$20:
	movq	(%rax,%rcx,8), %r10
	movq	40(%rsp), %r9
	movq	48(%rsp), %r8
	movq	56(%rsp), %r11
	movq	64(%rsp), %rbx
	movq	72(%rsp), %rbp
	xorq	80(%rsp), %r9
	xorq	88(%rsp), %r8
	xorq	96(%rsp), %r11
	xorq	104(%rsp), %rbx
	xorq	112(%rsp), %rbp
	xorq	120(%rsp), %r9
	xorq	128(%rsp), %r8
	xorq	136(%rsp), %r11
	xorq	144(%rsp), %rbx
	xorq	152(%rsp), %rbp
	xorq	160(%rsp), %r9
	xorq	168(%rsp), %r8
	xorq	176(%rsp), %r11
	xorq	184(%rsp), %rbx
	xorq	192(%rsp), %rbp
	xorq	200(%rsp), %r9
	xorq	208(%rsp), %r8
	xorq	216(%rsp), %r11
	xorq	224(%rsp), %rbx
	xorq	232(%rsp), %rbp
	movq	%r8, %rdx
	rolq	$1, %rdx
	xorq	%rbp, %rdx
	movq	%r11, %rsi
	rolq	$1, %rsi
	xorq	%r9, %rsi
	movq	%rbx, %rdi
	rolq	$1, %rdi
	xorq	%r8, %rdi
	movq	%rbp, %r8
	rolq	$1, %r8
	xorq	%r11, %r8
	rolq	$1, %r9
	xorq	%rbx, %r9
	movq	40(%rsp), %r11
	xorq	%rdx, %r11
	movq	88(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$44, %rbx
	movq	136(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$43, %rbp
	movq	184(%rsp), %r12
	xorq	%r8, %r12
	rolq	$21, %r12
	movq	232(%rsp), %r13
	xorq	%r9, %r13
	rolq	$14, %r13
	movq	%rbx, %r14
	notq	%r14
	andq	%rbp, %r14
	xorq	%r11, %r14
	xorq	%r10, %r14
	movq	%r14, 240(%rsp)
	movq	%rbp, %r10
	notq	%r10
	andq	%r12, %r10
	xorq	%rbx, %r10
	movq	%r10, 248(%rsp)
	movq	%r12, %r10
	notq	%r10
	andq	%r13, %r10
	xorq	%rbp, %r10
	movq	%r10, 256(%rsp)
	movq	%r13, %r10
	notq	%r10
	andq	%r11, %r10
	xorq	%r12, %r10
	movq	%r10, 264(%rsp)
	notq	%r11
	andq	%rbx, %r11
	xorq	%r13, %r11
	movq	%r11, 272(%rsp)
	movq	64(%rsp), %r10
	xorq	%r8, %r10
	rolq	$28, %r10
	movq	112(%rsp), %r11
	xorq	%r9, %r11
	rolq	$20, %r11
	movq	120(%rsp), %r12
	xorq	%rdx, %r12
	rolq	$3, %r12
	movq	168(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$45, %rbx
	movq	216(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$61, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 280(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 288(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 296(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 304(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 312(%rsp)
	movq	48(%rsp), %r10
	xorq	%rsi, %r10
	rolq	$1, %r10
	movq	96(%rsp), %r11
	xorq	%rdi, %r11
	rolq	$6, %r11
	movq	144(%rsp), %r12
	xorq	%r8, %r12
	rolq	$25, %r12
	movq	192(%rsp), %rbx
	xorq	%r9, %rbx
	rolq	$8, %rbx
	movq	200(%rsp), %rbp
	xorq	%rdx, %rbp
	rolq	$18, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 320(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 328(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 336(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 344(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 352(%rsp)
	movq	72(%rsp), %r10
	xorq	%r9, %r10
	rolq	$27, %r10
	movq	80(%rsp), %r11
	xorq	%rdx, %r11
	rolq	$36, %r11
	movq	128(%rsp), %r12
	xorq	%rsi, %r12
	rolq	$10, %r12
	movq	176(%rsp), %rbx
	xorq	%rdi, %rbx
	rolq	$15, %rbx
	movq	224(%rsp), %rbp
	xorq	%r8, %rbp
	rolq	$56, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 360(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 368(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 376(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 384(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 392(%rsp)
	movq	56(%rsp), %r10
	xorq	%rdi, %r10
	rolq	$62, %r10
	movq	104(%rsp), %rdi
	xorq	%r8, %rdi
	rolq	$55, %rdi
	movq	152(%rsp), %r8
	xorq	%r9, %r8
	rolq	$39, %r8
	movq	160(%rsp), %r9
	xorq	%rdx, %r9
	rolq	$41, %r9
	movq	208(%rsp), %rdx
	xorq	%rsi, %rdx
	rolq	$2, %rdx
	movq	%rdi, %rsi
	notq	%rsi
	andq	%r8, %rsi
	xorq	%r10, %rsi
	movq	%rsi, 400(%rsp)
	movq	%r8, %rsi
	notq	%rsi
	andq	%r9, %rsi
	xorq	%rdi, %rsi
	movq	%rsi, 408(%rsp)
	movq	%r9, %rsi
	notq	%rsi
	andq	%rdx, %rsi
	xorq	%r8, %rsi
	movq	%rsi, 416(%rsp)
	movq	%rdx, %rsi
	notq	%rsi
	andq	%r10, %rsi
	xorq	%r9, %rsi
	movq	%rsi, 424(%rsp)
	notq	%r10
	andq	%rdi, %r10
	xorq	%rdx, %r10
	movq	%r10, 432(%rsp)
	movq	8(%rax,%rcx,8), %r10
	movq	240(%rsp), %r9
	movq	248(%rsp), %r8
	movq	256(%rsp), %r11
	movq	264(%rsp), %rbx
	movq	272(%rsp), %rbp
	xorq	280(%rsp), %r9
	xorq	288(%rsp), %r8
	xorq	296(%rsp), %r11
	xorq	304(%rsp), %rbx
	xorq	312(%rsp), %rbp
	xorq	320(%rsp), %r9
	xorq	328(%rsp), %r8
	xorq	336(%rsp), %r11
	xorq	344(%rsp), %rbx
	xorq	352(%rsp), %rbp
	xorq	360(%rsp), %r9
	xorq	368(%rsp), %r8
	xorq	376(%rsp), %r11
	xorq	384(%rsp), %rbx
	xorq	392(%rsp), %rbp
	xorq	400(%rsp), %r9
	xorq	408(%rsp), %r8
	xorq	416(%rsp), %r11
	xorq	424(%rsp), %rbx
	xorq	432(%rsp), %rbp
	movq	%r8, %rdx
	rolq	$1, %rdx
	xorq	%rbp, %rdx
	movq	%r11, %rsi
	rolq	$1, %rsi
	xorq	%r9, %rsi
	movq	%rbx, %rdi
	rolq	$1, %rdi
	xorq	%r8, %rdi
	movq	%rbp, %r8
	rolq	$1, %r8
	xorq	%r11, %r8
	rolq	$1, %r9
	xorq	%rbx, %r9
	movq	240(%rsp), %r11
	xorq	%rdx, %r11
	movq	288(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$44, %rbx
	movq	336(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$43, %rbp
	movq	384(%rsp), %r12
	xorq	%r8, %r12
	rolq	$21, %r12
	movq	432(%rsp), %r13
	xorq	%r9, %r13
	rolq	$14, %r13
	movq	%rbx, %r14
	notq	%r14
	andq	%rbp, %r14
	xorq	%r11, %r14
	xorq	%r10, %r14
	movq	%r14, 40(%rsp)
	movq	%rbp, %r10
	notq	%r10
	andq	%r12, %r10
	xorq	%rbx, %r10
	movq	%r10, 48(%rsp)
	movq	%r12, %r10
	notq	%r10
	andq	%r13, %r10
	xorq	%rbp, %r10
	movq	%r10, 56(%rsp)
	movq	%r13, %r10
	notq	%r10
	andq	%r11, %r10
	xorq	%r12, %r10
	movq	%r10, 64(%rsp)
	notq	%r11
	andq	%rbx, %r11
	xorq	%r13, %r11
	movq	%r11, 72(%rsp)
	movq	264(%rsp), %r10
	xorq	%r8, %r10
	rolq	$28, %r10
	movq	312(%rsp), %r11
	xorq	%r9, %r11
	rolq	$20, %r11
	movq	320(%rsp), %r12
	xorq	%rdx, %r12
	rolq	$3, %r12
	movq	368(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$45, %rbx
	movq	416(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$61, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 80(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 88(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 96(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 104(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 112(%rsp)
	movq	248(%rsp), %r10
	xorq	%rsi, %r10
	rolq	$1, %r10
	movq	296(%rsp), %r11
	xorq	%rdi, %r11
	rolq	$6, %r11
	movq	344(%rsp), %r12
	xorq	%r8, %r12
	rolq	$25, %r12
	movq	392(%rsp), %rbx
	xorq	%r9, %rbx
	rolq	$8, %rbx
	movq	400(%rsp), %rbp
	xorq	%rdx, %rbp
	rolq	$18, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 120(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 128(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 136(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 144(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 152(%rsp)
	movq	272(%rsp), %r10
	xorq	%r9, %r10
	rolq	$27, %r10
	movq	280(%rsp), %r11
	xorq	%rdx, %r11
	rolq	$36, %r11
	movq	328(%rsp), %r12
	xorq	%rsi, %r12
	rolq	$10, %r12
	movq	376(%rsp), %rbx
	xorq	%rdi, %rbx
	rolq	$15, %rbx
	movq	424(%rsp), %rbp
	xorq	%r8, %rbp
	rolq	$56, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 160(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 168(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 176(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 184(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 192(%rsp)
	movq	256(%rsp), %r10
	xorq	%rdi, %r10
	rolq	$62, %r10
	movq	304(%rsp), %rdi
	xorq	%r8, %rdi
	rolq	$55, %rdi
	movq	352(%rsp), %r8
	xorq	%r9, %r8
	rolq	$39, %r8
	movq	360(%rsp), %r9
	xorq	%rdx, %r9
	rolq	$41, %r9
	movq	408(%rsp), %rdx
	xorq	%rsi, %rdx
	rolq	$2, %rdx
	movq	%rdi, %rsi
	notq	%rsi
	andq	%r8, %rsi
	xorq	%r10, %rsi
	movq	%rsi, 200(%rsp)
	movq	%r8, %rsi
	notq	%rsi
	andq	%r9, %rsi
	xorq	%rdi, %rsi
	movq	%rsi, 208(%rsp)
	movq	%r9, %rsi
	notq	%rsi
	andq	%rdx, %rsi
	xorq	%r8, %rsi
	movq	%rsi, 216(%rsp)
	movq	%rdx, %rsi
	notq	%rsi
	andq	%r10, %rsi
	xorq	%r9, %rsi
	movq	%rsi, 224(%rsp)
	notq	%r10
	andq	%rdi, %r10
	xorq	%rdx, %r10
	movq	%r10, 232(%rsp)
	addq	$2, %rcx
L_keccak1600_ref$19:
	cmpq	$23, %rcx
	jb  	L_keccak1600_ref$20
	movq	16(%rsp), %rdx
	movq	24(%rsp), %rcx
	movq	32(%rsp), %r9
L_keccak1600_ref$17:
	cmpq	%r9, %rcx
	jnb 	L_keccak1600_ref$18
	movb	440(%rsp), %al
	movq	%rcx, %rsi
	shrq	$3, %rsi
	movq	$0, %rdi
	jmp 	L_keccak1600_ref$15
L_keccak1600_ref$16:
	movq	(%rdx,%rdi,8), %r8
	xorq	%r8, 40(%rsp,%rdi,8)
	incq	%rdi
L_keccak1600_ref$15:
	cmpq	%rsi, %rdi
	jb  	L_keccak1600_ref$16
	shlq	$3, %rdi
	jmp 	L_keccak1600_ref$13
L_keccak1600_ref$14:
	movb	(%rdx,%rdi), %sil
	xorb	%sil, 40(%rsp,%rdi)
	incq	%rdi
L_keccak1600_ref$13:
	cmpq	%rcx, %rdi
	jb  	L_keccak1600_ref$14
	xorb	%al, 40(%rsp,%rdi)
	movq	%r9, %rax
	addq	$-1, %rax
	xorb	$128, 40(%rsp,%rax)
	movq	8(%rsp), %rcx
	jmp 	L_keccak1600_ref$7
L_keccak1600_ref$8:
	movq	%rcx, 8(%rsp)
	movq	%r9, 32(%rsp)
	leaq	glob_data + 0(%rip), %rax
	movq	$0, %rcx
	jmp 	L_keccak1600_ref$11
L_keccak1600_ref$12:
	movq	(%rax,%rcx,8), %r10
	movq	40(%rsp), %r9
	movq	48(%rsp), %r8
	movq	56(%rsp), %r11
	movq	64(%rsp), %rbx
	movq	72(%rsp), %rbp
	xorq	80(%rsp), %r9
	xorq	88(%rsp), %r8
	xorq	96(%rsp), %r11
	xorq	104(%rsp), %rbx
	xorq	112(%rsp), %rbp
	xorq	120(%rsp), %r9
	xorq	128(%rsp), %r8
	xorq	136(%rsp), %r11
	xorq	144(%rsp), %rbx
	xorq	152(%rsp), %rbp
	xorq	160(%rsp), %r9
	xorq	168(%rsp), %r8
	xorq	176(%rsp), %r11
	xorq	184(%rsp), %rbx
	xorq	192(%rsp), %rbp
	xorq	200(%rsp), %r9
	xorq	208(%rsp), %r8
	xorq	216(%rsp), %r11
	xorq	224(%rsp), %rbx
	xorq	232(%rsp), %rbp
	movq	%r8, %rdx
	rolq	$1, %rdx
	xorq	%rbp, %rdx
	movq	%r11, %rsi
	rolq	$1, %rsi
	xorq	%r9, %rsi
	movq	%rbx, %rdi
	rolq	$1, %rdi
	xorq	%r8, %rdi
	movq	%rbp, %r8
	rolq	$1, %r8
	xorq	%r11, %r8
	rolq	$1, %r9
	xorq	%rbx, %r9
	movq	40(%rsp), %r11
	xorq	%rdx, %r11
	movq	88(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$44, %rbx
	movq	136(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$43, %rbp
	movq	184(%rsp), %r12
	xorq	%r8, %r12
	rolq	$21, %r12
	movq	232(%rsp), %r13
	xorq	%r9, %r13
	rolq	$14, %r13
	movq	%rbx, %r14
	notq	%r14
	andq	%rbp, %r14
	xorq	%r11, %r14
	xorq	%r10, %r14
	movq	%r14, 240(%rsp)
	movq	%rbp, %r10
	notq	%r10
	andq	%r12, %r10
	xorq	%rbx, %r10
	movq	%r10, 248(%rsp)
	movq	%r12, %r10
	notq	%r10
	andq	%r13, %r10
	xorq	%rbp, %r10
	movq	%r10, 256(%rsp)
	movq	%r13, %r10
	notq	%r10
	andq	%r11, %r10
	xorq	%r12, %r10
	movq	%r10, 264(%rsp)
	notq	%r11
	andq	%rbx, %r11
	xorq	%r13, %r11
	movq	%r11, 272(%rsp)
	movq	64(%rsp), %r10
	xorq	%r8, %r10
	rolq	$28, %r10
	movq	112(%rsp), %r11
	xorq	%r9, %r11
	rolq	$20, %r11
	movq	120(%rsp), %r12
	xorq	%rdx, %r12
	rolq	$3, %r12
	movq	168(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$45, %rbx
	movq	216(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$61, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 280(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 288(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 296(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 304(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 312(%rsp)
	movq	48(%rsp), %r10
	xorq	%rsi, %r10
	rolq	$1, %r10
	movq	96(%rsp), %r11
	xorq	%rdi, %r11
	rolq	$6, %r11
	movq	144(%rsp), %r12
	xorq	%r8, %r12
	rolq	$25, %r12
	movq	192(%rsp), %rbx
	xorq	%r9, %rbx
	rolq	$8, %rbx
	movq	200(%rsp), %rbp
	xorq	%rdx, %rbp
	rolq	$18, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 320(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 328(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 336(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 344(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 352(%rsp)
	movq	72(%rsp), %r10
	xorq	%r9, %r10
	rolq	$27, %r10
	movq	80(%rsp), %r11
	xorq	%rdx, %r11
	rolq	$36, %r11
	movq	128(%rsp), %r12
	xorq	%rsi, %r12
	rolq	$10, %r12
	movq	176(%rsp), %rbx
	xorq	%rdi, %rbx
	rolq	$15, %rbx
	movq	224(%rsp), %rbp
	xorq	%r8, %rbp
	rolq	$56, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 360(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 368(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 376(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 384(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 392(%rsp)
	movq	56(%rsp), %r10
	xorq	%rdi, %r10
	rolq	$62, %r10
	movq	104(%rsp), %rdi
	xorq	%r8, %rdi
	rolq	$55, %rdi
	movq	152(%rsp), %r8
	xorq	%r9, %r8
	rolq	$39, %r8
	movq	160(%rsp), %r9
	xorq	%rdx, %r9
	rolq	$41, %r9
	movq	208(%rsp), %rdx
	xorq	%rsi, %rdx
	rolq	$2, %rdx
	movq	%rdi, %rsi
	notq	%rsi
	andq	%r8, %rsi
	xorq	%r10, %rsi
	movq	%rsi, 400(%rsp)
	movq	%r8, %rsi
	notq	%rsi
	andq	%r9, %rsi
	xorq	%rdi, %rsi
	movq	%rsi, 408(%rsp)
	movq	%r9, %rsi
	notq	%rsi
	andq	%rdx, %rsi
	xorq	%r8, %rsi
	movq	%rsi, 416(%rsp)
	movq	%rdx, %rsi
	notq	%rsi
	andq	%r10, %rsi
	xorq	%r9, %rsi
	movq	%rsi, 424(%rsp)
	notq	%r10
	andq	%rdi, %r10
	xorq	%rdx, %r10
	movq	%r10, 432(%rsp)
	movq	8(%rax,%rcx,8), %r10
	movq	240(%rsp), %r9
	movq	248(%rsp), %r8
	movq	256(%rsp), %r11
	movq	264(%rsp), %rbx
	movq	272(%rsp), %rbp
	xorq	280(%rsp), %r9
	xorq	288(%rsp), %r8
	xorq	296(%rsp), %r11
	xorq	304(%rsp), %rbx
	xorq	312(%rsp), %rbp
	xorq	320(%rsp), %r9
	xorq	328(%rsp), %r8
	xorq	336(%rsp), %r11
	xorq	344(%rsp), %rbx
	xorq	352(%rsp), %rbp
	xorq	360(%rsp), %r9
	xorq	368(%rsp), %r8
	xorq	376(%rsp), %r11
	xorq	384(%rsp), %rbx
	xorq	392(%rsp), %rbp
	xorq	400(%rsp), %r9
	xorq	408(%rsp), %r8
	xorq	416(%rsp), %r11
	xorq	424(%rsp), %rbx
	xorq	432(%rsp), %rbp
	movq	%r8, %rdx
	rolq	$1, %rdx
	xorq	%rbp, %rdx
	movq	%r11, %rsi
	rolq	$1, %rsi
	xorq	%r9, %rsi
	movq	%rbx, %rdi
	rolq	$1, %rdi
	xorq	%r8, %rdi
	movq	%rbp, %r8
	rolq	$1, %r8
	xorq	%r11, %r8
	rolq	$1, %r9
	xorq	%rbx, %r9
	movq	240(%rsp), %r11
	xorq	%rdx, %r11
	movq	288(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$44, %rbx
	movq	336(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$43, %rbp
	movq	384(%rsp), %r12
	xorq	%r8, %r12
	rolq	$21, %r12
	movq	432(%rsp), %r13
	xorq	%r9, %r13
	rolq	$14, %r13
	movq	%rbx, %r14
	notq	%r14
	andq	%rbp, %r14
	xorq	%r11, %r14
	xorq	%r10, %r14
	movq	%r14, 40(%rsp)
	movq	%rbp, %r10
	notq	%r10
	andq	%r12, %r10
	xorq	%rbx, %r10
	movq	%r10, 48(%rsp)
	movq	%r12, %r10
	notq	%r10
	andq	%r13, %r10
	xorq	%rbp, %r10
	movq	%r10, 56(%rsp)
	movq	%r13, %r10
	notq	%r10
	andq	%r11, %r10
	xorq	%r12, %r10
	movq	%r10, 64(%rsp)
	notq	%r11
	andq	%rbx, %r11
	xorq	%r13, %r11
	movq	%r11, 72(%rsp)
	movq	264(%rsp), %r10
	xorq	%r8, %r10
	rolq	$28, %r10
	movq	312(%rsp), %r11
	xorq	%r9, %r11
	rolq	$20, %r11
	movq	320(%rsp), %r12
	xorq	%rdx, %r12
	rolq	$3, %r12
	movq	368(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$45, %rbx
	movq	416(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$61, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 80(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 88(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 96(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 104(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 112(%rsp)
	movq	248(%rsp), %r10
	xorq	%rsi, %r10
	rolq	$1, %r10
	movq	296(%rsp), %r11
	xorq	%rdi, %r11
	rolq	$6, %r11
	movq	344(%rsp), %r12
	xorq	%r8, %r12
	rolq	$25, %r12
	movq	392(%rsp), %rbx
	xorq	%r9, %rbx
	rolq	$8, %rbx
	movq	400(%rsp), %rbp
	xorq	%rdx, %rbp
	rolq	$18, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 120(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 128(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 136(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 144(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 152(%rsp)
	movq	272(%rsp), %r10
	xorq	%r9, %r10
	rolq	$27, %r10
	movq	280(%rsp), %r11
	xorq	%rdx, %r11
	rolq	$36, %r11
	movq	328(%rsp), %r12
	xorq	%rsi, %r12
	rolq	$10, %r12
	movq	376(%rsp), %rbx
	xorq	%rdi, %rbx
	rolq	$15, %rbx
	movq	424(%rsp), %rbp
	xorq	%r8, %rbp
	rolq	$56, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 160(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 168(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 176(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 184(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 192(%rsp)
	movq	256(%rsp), %r10
	xorq	%rdi, %r10
	rolq	$62, %r10
	movq	304(%rsp), %rdi
	xorq	%r8, %rdi
	rolq	$55, %rdi
	movq	352(%rsp), %r8
	xorq	%r9, %r8
	rolq	$39, %r8
	movq	360(%rsp), %r9
	xorq	%rdx, %r9
	rolq	$41, %r9
	movq	408(%rsp), %rdx
	xorq	%rsi, %rdx
	rolq	$2, %rdx
	movq	%rdi, %rsi
	notq	%rsi
	andq	%r8, %rsi
	xorq	%r10, %rsi
	movq	%rsi, 200(%rsp)
	movq	%r8, %rsi
	notq	%rsi
	andq	%r9, %rsi
	xorq	%rdi, %rsi
	movq	%rsi, 208(%rsp)
	movq	%r9, %rsi
	notq	%rsi
	andq	%rdx, %rsi
	xorq	%r8, %rsi
	movq	%rsi, 216(%rsp)
	movq	%rdx, %rsi
	notq	%rsi
	andq	%r10, %rsi
	xorq	%r9, %rsi
	movq	%rsi, 224(%rsp)
	notq	%r10
	andq	%rdi, %r10
	xorq	%rdx, %r10
	movq	%r10, 232(%rsp)
	addq	$2, %rcx
L_keccak1600_ref$11:
	cmpq	$23, %rcx
	jb  	L_keccak1600_ref$12
	movq	(%rsp), %rax
	movq	8(%rsp), %rcx
	movq	32(%rsp), %r9
	movq	%r9, %rdx
	shrq	$3, %rdx
	movq	$0, %rsi
	jmp 	L_keccak1600_ref$9
L_keccak1600_ref$10:
	movq	40(%rsp,%rsi,8), %rdi
	movq	%rdi, (%rax,%rsi,8)
	incq	%rsi
L_keccak1600_ref$9:
	cmpq	%rdx, %rsi
	jb  	L_keccak1600_ref$10
	addq	%r9, %rax
	subq	%r9, %rcx
	movq	%rax, (%rsp)
L_keccak1600_ref$7:
	cmpq	%r9, %rcx
	jnbe	L_keccak1600_ref$8
	movq	%rcx, 32(%rsp)
	leaq	glob_data + 0(%rip), %rax
	movq	$0, %rcx
	jmp 	L_keccak1600_ref$5
L_keccak1600_ref$6:
	movq	(%rax,%rcx,8), %r10
	movq	40(%rsp), %r9
	movq	48(%rsp), %r8
	movq	56(%rsp), %r11
	movq	64(%rsp), %rbx
	movq	72(%rsp), %rbp
	xorq	80(%rsp), %r9
	xorq	88(%rsp), %r8
	xorq	96(%rsp), %r11
	xorq	104(%rsp), %rbx
	xorq	112(%rsp), %rbp
	xorq	120(%rsp), %r9
	xorq	128(%rsp), %r8
	xorq	136(%rsp), %r11
	xorq	144(%rsp), %rbx
	xorq	152(%rsp), %rbp
	xorq	160(%rsp), %r9
	xorq	168(%rsp), %r8
	xorq	176(%rsp), %r11
	xorq	184(%rsp), %rbx
	xorq	192(%rsp), %rbp
	xorq	200(%rsp), %r9
	xorq	208(%rsp), %r8
	xorq	216(%rsp), %r11
	xorq	224(%rsp), %rbx
	xorq	232(%rsp), %rbp
	movq	%r8, %rdx
	rolq	$1, %rdx
	xorq	%rbp, %rdx
	movq	%r11, %rsi
	rolq	$1, %rsi
	xorq	%r9, %rsi
	movq	%rbx, %rdi
	rolq	$1, %rdi
	xorq	%r8, %rdi
	movq	%rbp, %r8
	rolq	$1, %r8
	xorq	%r11, %r8
	rolq	$1, %r9
	xorq	%rbx, %r9
	movq	40(%rsp), %r11
	xorq	%rdx, %r11
	movq	88(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$44, %rbx
	movq	136(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$43, %rbp
	movq	184(%rsp), %r12
	xorq	%r8, %r12
	rolq	$21, %r12
	movq	232(%rsp), %r13
	xorq	%r9, %r13
	rolq	$14, %r13
	movq	%rbx, %r14
	notq	%r14
	andq	%rbp, %r14
	xorq	%r11, %r14
	xorq	%r10, %r14
	movq	%r14, 240(%rsp)
	movq	%rbp, %r10
	notq	%r10
	andq	%r12, %r10
	xorq	%rbx, %r10
	movq	%r10, 248(%rsp)
	movq	%r12, %r10
	notq	%r10
	andq	%r13, %r10
	xorq	%rbp, %r10
	movq	%r10, 256(%rsp)
	movq	%r13, %r10
	notq	%r10
	andq	%r11, %r10
	xorq	%r12, %r10
	movq	%r10, 264(%rsp)
	notq	%r11
	andq	%rbx, %r11
	xorq	%r13, %r11
	movq	%r11, 272(%rsp)
	movq	64(%rsp), %r10
	xorq	%r8, %r10
	rolq	$28, %r10
	movq	112(%rsp), %r11
	xorq	%r9, %r11
	rolq	$20, %r11
	movq	120(%rsp), %r12
	xorq	%rdx, %r12
	rolq	$3, %r12
	movq	168(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$45, %rbx
	movq	216(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$61, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 280(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 288(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 296(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 304(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 312(%rsp)
	movq	48(%rsp), %r10
	xorq	%rsi, %r10
	rolq	$1, %r10
	movq	96(%rsp), %r11
	xorq	%rdi, %r11
	rolq	$6, %r11
	movq	144(%rsp), %r12
	xorq	%r8, %r12
	rolq	$25, %r12
	movq	192(%rsp), %rbx
	xorq	%r9, %rbx
	rolq	$8, %rbx
	movq	200(%rsp), %rbp
	xorq	%rdx, %rbp
	rolq	$18, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 320(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 328(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 336(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 344(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 352(%rsp)
	movq	72(%rsp), %r10
	xorq	%r9, %r10
	rolq	$27, %r10
	movq	80(%rsp), %r11
	xorq	%rdx, %r11
	rolq	$36, %r11
	movq	128(%rsp), %r12
	xorq	%rsi, %r12
	rolq	$10, %r12
	movq	176(%rsp), %rbx
	xorq	%rdi, %rbx
	rolq	$15, %rbx
	movq	224(%rsp), %rbp
	xorq	%r8, %rbp
	rolq	$56, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 360(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 368(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 376(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 384(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 392(%rsp)
	movq	56(%rsp), %r10
	xorq	%rdi, %r10
	rolq	$62, %r10
	movq	104(%rsp), %rdi
	xorq	%r8, %rdi
	rolq	$55, %rdi
	movq	152(%rsp), %r8
	xorq	%r9, %r8
	rolq	$39, %r8
	movq	160(%rsp), %r9
	xorq	%rdx, %r9
	rolq	$41, %r9
	movq	208(%rsp), %rdx
	xorq	%rsi, %rdx
	rolq	$2, %rdx
	movq	%rdi, %rsi
	notq	%rsi
	andq	%r8, %rsi
	xorq	%r10, %rsi
	movq	%rsi, 400(%rsp)
	movq	%r8, %rsi
	notq	%rsi
	andq	%r9, %rsi
	xorq	%rdi, %rsi
	movq	%rsi, 408(%rsp)
	movq	%r9, %rsi
	notq	%rsi
	andq	%rdx, %rsi
	xorq	%r8, %rsi
	movq	%rsi, 416(%rsp)
	movq	%rdx, %rsi
	notq	%rsi
	andq	%r10, %rsi
	xorq	%r9, %rsi
	movq	%rsi, 424(%rsp)
	notq	%r10
	andq	%rdi, %r10
	xorq	%rdx, %r10
	movq	%r10, 432(%rsp)
	movq	8(%rax,%rcx,8), %r10
	movq	240(%rsp), %r9
	movq	248(%rsp), %r8
	movq	256(%rsp), %r11
	movq	264(%rsp), %rbx
	movq	272(%rsp), %rbp
	xorq	280(%rsp), %r9
	xorq	288(%rsp), %r8
	xorq	296(%rsp), %r11
	xorq	304(%rsp), %rbx
	xorq	312(%rsp), %rbp
	xorq	320(%rsp), %r9
	xorq	328(%rsp), %r8
	xorq	336(%rsp), %r11
	xorq	344(%rsp), %rbx
	xorq	352(%rsp), %rbp
	xorq	360(%rsp), %r9
	xorq	368(%rsp), %r8
	xorq	376(%rsp), %r11
	xorq	384(%rsp), %rbx
	xorq	392(%rsp), %rbp
	xorq	400(%rsp), %r9
	xorq	408(%rsp), %r8
	xorq	416(%rsp), %r11
	xorq	424(%rsp), %rbx
	xorq	432(%rsp), %rbp
	movq	%r8, %rdx
	rolq	$1, %rdx
	xorq	%rbp, %rdx
	movq	%r11, %rsi
	rolq	$1, %rsi
	xorq	%r9, %rsi
	movq	%rbx, %rdi
	rolq	$1, %rdi
	xorq	%r8, %rdi
	movq	%rbp, %r8
	rolq	$1, %r8
	xorq	%r11, %r8
	rolq	$1, %r9
	xorq	%rbx, %r9
	movq	240(%rsp), %r11
	xorq	%rdx, %r11
	movq	288(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$44, %rbx
	movq	336(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$43, %rbp
	movq	384(%rsp), %r12
	xorq	%r8, %r12
	rolq	$21, %r12
	movq	432(%rsp), %r13
	xorq	%r9, %r13
	rolq	$14, %r13
	movq	%rbx, %r14
	notq	%r14
	andq	%rbp, %r14
	xorq	%r11, %r14
	xorq	%r10, %r14
	movq	%r14, 40(%rsp)
	movq	%rbp, %r10
	notq	%r10
	andq	%r12, %r10
	xorq	%rbx, %r10
	movq	%r10, 48(%rsp)
	movq	%r12, %r10
	notq	%r10
	andq	%r13, %r10
	xorq	%rbp, %r10
	movq	%r10, 56(%rsp)
	movq	%r13, %r10
	notq	%r10
	andq	%r11, %r10
	xorq	%r12, %r10
	movq	%r10, 64(%rsp)
	notq	%r11
	andq	%rbx, %r11
	xorq	%r13, %r11
	movq	%r11, 72(%rsp)
	movq	264(%rsp), %r10
	xorq	%r8, %r10
	rolq	$28, %r10
	movq	312(%rsp), %r11
	xorq	%r9, %r11
	rolq	$20, %r11
	movq	320(%rsp), %r12
	xorq	%rdx, %r12
	rolq	$3, %r12
	movq	368(%rsp), %rbx
	xorq	%rsi, %rbx
	rolq	$45, %rbx
	movq	416(%rsp), %rbp
	xorq	%rdi, %rbp
	rolq	$61, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 80(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 88(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 96(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 104(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 112(%rsp)
	movq	248(%rsp), %r10
	xorq	%rsi, %r10
	rolq	$1, %r10
	movq	296(%rsp), %r11
	xorq	%rdi, %r11
	rolq	$6, %r11
	movq	344(%rsp), %r12
	xorq	%r8, %r12
	rolq	$25, %r12
	movq	392(%rsp), %rbx
	xorq	%r9, %rbx
	rolq	$8, %rbx
	movq	400(%rsp), %rbp
	xorq	%rdx, %rbp
	rolq	$18, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 120(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 128(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 136(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 144(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 152(%rsp)
	movq	272(%rsp), %r10
	xorq	%r9, %r10
	rolq	$27, %r10
	movq	280(%rsp), %r11
	xorq	%rdx, %r11
	rolq	$36, %r11
	movq	328(%rsp), %r12
	xorq	%rsi, %r12
	rolq	$10, %r12
	movq	376(%rsp), %rbx
	xorq	%rdi, %rbx
	rolq	$15, %rbx
	movq	424(%rsp), %rbp
	xorq	%r8, %rbp
	rolq	$56, %rbp
	movq	%r11, %r13
	notq	%r13
	andq	%r12, %r13
	xorq	%r10, %r13
	movq	%r13, 160(%rsp)
	movq	%r12, %r13
	notq	%r13
	andq	%rbx, %r13
	xorq	%r11, %r13
	movq	%r13, 168(%rsp)
	movq	%rbx, %r13
	notq	%r13
	andq	%rbp, %r13
	xorq	%r12, %r13
	movq	%r13, 176(%rsp)
	movq	%rbp, %r12
	notq	%r12
	andq	%r10, %r12
	xorq	%rbx, %r12
	movq	%r12, 184(%rsp)
	notq	%r10
	andq	%r11, %r10
	xorq	%rbp, %r10
	movq	%r10, 192(%rsp)
	movq	256(%rsp), %r10
	xorq	%rdi, %r10
	rolq	$62, %r10
	movq	304(%rsp), %rdi
	xorq	%r8, %rdi
	rolq	$55, %rdi
	movq	352(%rsp), %r8
	xorq	%r9, %r8
	rolq	$39, %r8
	movq	360(%rsp), %r9
	xorq	%rdx, %r9
	rolq	$41, %r9
	movq	408(%rsp), %rdx
	xorq	%rsi, %rdx
	rolq	$2, %rdx
	movq	%rdi, %rsi
	notq	%rsi
	andq	%r8, %rsi
	xorq	%r10, %rsi
	movq	%rsi, 200(%rsp)
	movq	%r8, %rsi
	notq	%rsi
	andq	%r9, %rsi
	xorq	%rdi, %rsi
	movq	%rsi, 208(%rsp)
	movq	%r9, %rsi
	notq	%rsi
	andq	%rdx, %rsi
	xorq	%r8, %rsi
	movq	%rsi, 216(%rsp)
	movq	%rdx, %rsi
	notq	%rsi
	andq	%r10, %rsi
	xorq	%r9, %rsi
	movq	%rsi, 224(%rsp)
	notq	%r10
	andq	%rdi, %r10
	xorq	%rdx, %r10
	movq	%r10, 232(%rsp)
	addq	$2, %rcx
L_keccak1600_ref$5:
	cmpq	$23, %rcx
	jb  	L_keccak1600_ref$6
	movq	(%rsp), %rax
	movq	32(%rsp), %rcx
	movq	%rcx, %rdx
	shrq	$3, %rdx
	movq	$0, %rsi
	jmp 	L_keccak1600_ref$3
L_keccak1600_ref$4:
	movq	40(%rsp,%rsi,8), %rdi
	movq	%rdi, (%rax,%rsi,8)
	incq	%rsi
L_keccak1600_ref$3:
	cmpq	%rdx, %rsi
	jb  	L_keccak1600_ref$4
	shlq	$3, %rsi
	jmp 	L_keccak1600_ref$1
L_keccak1600_ref$2:
	movb	40(%rsp,%rsi), %dl
	movb	%dl, (%rax,%rsi)
	incq	%rsi
L_keccak1600_ref$1:
	cmpq	%rcx, %rsi
	jb  	L_keccak1600_ref$2
	movq	448(%rsp), %rbx
	movq	456(%rsp), %rbp
	movq	464(%rsp), %r12
	movq	472(%rsp), %r13
	movq	480(%rsp), %r14
	movq	488(%rsp), %rsp
	ret
	.data
	.p2align	5
_glob_data:
glob_data:
G$KECCAK1600_RC:
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-126
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-118
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-117
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-127
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	9
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-118
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-120
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	9
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	10
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-117
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-117
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-119
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	3
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	2
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	10
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	10
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-127
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-128
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	1
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
