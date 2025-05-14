	.att_syntax
	.text
	.p2align	5
	.globl	__keccak1600_avx2
	.globl	_keccak1600_avx2
__keccak1600_avx2:
_keccak1600_avx2:
	movq	%rsp, %rax
	leaq	-256(%rsp), %rsp
	andq	$-32, %rsp
	movq	%rbx, 224(%rsp)
	movq	%rbp, 232(%rsp)
	movq	%r12, 240(%rsp)
	movq	%rax, 248(%rsp)
	vpxor	%ymm6, %ymm6, %ymm6
	vpxor	%ymm3, %ymm3, %ymm3
	vpxor	%ymm4, %ymm4, %ymm4
	vpxor	%ymm0, %ymm0, %ymm0
	vpxor	%ymm5, %ymm5, %ymm5
	vpxor	%ymm1, %ymm1, %ymm1
	vpxor	%ymm2, %ymm2, %ymm2
	leaq	glob_data + 1152(%rip), %rax
	vpxor	%ymm7, %ymm7, %ymm7
	vmovdqu	%ymm7, (%rsp)
	vmovdqu	%ymm7, 32(%rsp)
	vmovdqu	%ymm7, 64(%rsp)
	vmovdqu	%ymm7, 96(%rsp)
	vmovdqu	%ymm7, 128(%rsp)
	vmovdqu	%ymm7, 160(%rsp)
	vmovdqu	%ymm7, 192(%rsp)
	jmp 	L_keccak1600_avx2$15
L_keccak1600_avx2$16:
	movq	%r9, %r10
	shrq	$3, %r10
	movq	$0, %r11
	jmp 	L_keccak1600_avx2$18
L_keccak1600_avx2$19:
	movq	(%rdx,%r11,8), %rbx
	movq	(%rax,%r11,8), %rbp
	movq	%rbx, (%rsp,%rbp,8)
	incq	%r11
L_keccak1600_avx2$18:
	cmpq	%r10, %r11
	jb  	L_keccak1600_avx2$19
	movq	(%rsp), %r10
	movq	%r10, 8(%rsp)
	movq	%r10, 16(%rsp)
	movq	%r10, 24(%rsp)
	vpxor	(%rsp), %ymm6, %ymm6
	vpxor	32(%rsp), %ymm3, %ymm3
	vpxor	64(%rsp), %ymm4, %ymm4
	vpxor	96(%rsp), %ymm0, %ymm0
	vpxor	128(%rsp), %ymm5, %ymm5
	vpxor	160(%rsp), %ymm1, %ymm1
	vpxor	192(%rsp), %ymm2, %ymm2
	addq	%r9, %rdx
	subq	%r9, %rcx
	leaq	glob_data + 384(%rip), %r10
	movq	$0, %r11
	leaq	glob_data + 192(%rip), %rbx
	leaq	glob_data + 0(%rip), %rbp
	movq	$24, %r12
L_keccak1600_avx2$17:
	vpshufd	$78, %ymm4, %ymm8
	vpxor	%ymm0, %ymm1, %ymm7
	vpxor	%ymm2, %ymm5, %ymm9
	vpxor	%ymm3, %ymm7, %ymm7
	vpxor	%ymm9, %ymm7, %ymm10
	vpermq	$147, %ymm10, %ymm7
	vpxor	%ymm4, %ymm8, %ymm8
	vpermq	$78, %ymm8, %ymm9
	vpsrlq	$63, %ymm10, %ymm11
	vpaddq	%ymm10, %ymm10, %ymm10
	vpor	%ymm10, %ymm11, %ymm11
	vpermq	$57, %ymm11, %ymm10
	vpxor	%ymm7, %ymm11, %ymm11
	vpermq	$0, %ymm11, %ymm11
	vpxor	%ymm6, %ymm8, %ymm8
	vpxor	%ymm9, %ymm8, %ymm8
	vpsrlq	$63, %ymm8, %ymm9
	vpaddq	%ymm8, %ymm8, %ymm12
	vpor	%ymm9, %ymm12, %ymm9
	vpxor	%ymm11, %ymm4, %ymm4
	vpxor	%ymm11, %ymm6, %ymm6
	vpblendd	$192, %ymm9, %ymm10, %ymm9
	vpblendd	$3, %ymm8, %ymm7, %ymm7
	vpxor	%ymm7, %ymm9, %ymm9
	vpsllvq	(%rbx), %ymm4, %ymm7
	vpsrlvq	(%rbp), %ymm4, %ymm4
	vpor	%ymm7, %ymm4, %ymm4
	vpxor	%ymm9, %ymm0, %ymm0
	vpsllvq	64(%rbx), %ymm0, %ymm7
	vpsrlvq	64(%rbp), %ymm0, %ymm0
	vpor	%ymm7, %ymm0, %ymm0
	vpxor	%ymm9, %ymm5, %ymm5
	vpsllvq	96(%rbx), %ymm5, %ymm7
	vpsrlvq	96(%rbp), %ymm5, %ymm5
	vpor	%ymm7, %ymm5, %ymm10
	vpxor	%ymm9, %ymm1, %ymm1
	vpsllvq	128(%rbx), %ymm1, %ymm5
	vpsrlvq	128(%rbp), %ymm1, %ymm1
	vpor	%ymm5, %ymm1, %ymm1
	vpxor	%ymm9, %ymm2, %ymm2
	vpermq	$141, %ymm4, %ymm5
	vpermq	$141, %ymm0, %ymm7
	vpsllvq	160(%rbx), %ymm2, %ymm0
	vpsrlvq	160(%rbp), %ymm2, %ymm2
	vpor	%ymm0, %ymm2, %ymm8
	vpxor	%ymm9, %ymm3, %ymm0
	vpermq	$27, %ymm10, %ymm3
	vpermq	$114, %ymm1, %ymm9
	vpsllvq	32(%rbx), %ymm0, %ymm1
	vpsrlvq	32(%rbp), %ymm0, %ymm0
	vpor	%ymm1, %ymm0, %ymm10
	vpsrldq	$8, %ymm8, %ymm0
	vpandn	%ymm0, %ymm8, %ymm0
	vpblendd	$12, %ymm9, %ymm10, %ymm1
	vpblendd	$12, %ymm10, %ymm7, %ymm2
	vpblendd	$12, %ymm7, %ymm5, %ymm4
	vpblendd	$12, %ymm5, %ymm10, %ymm11
	vpblendd	$48, %ymm7, %ymm1, %ymm1
	vpblendd	$48, %ymm3, %ymm2, %ymm2
	vpblendd	$48, %ymm10, %ymm4, %ymm4
	vpblendd	$48, %ymm9, %ymm11, %ymm11
	vpblendd	$192, %ymm3, %ymm1, %ymm1
	vpblendd	$192, %ymm9, %ymm2, %ymm2
	vpblendd	$192, %ymm9, %ymm4, %ymm4
	vpblendd	$192, %ymm7, %ymm11, %ymm11
	vpandn	%ymm2, %ymm1, %ymm1
	vpandn	%ymm11, %ymm4, %ymm2
	vpblendd	$12, %ymm10, %ymm3, %ymm4
	vpblendd	$12, %ymm3, %ymm5, %ymm11
	vpxor	%ymm5, %ymm1, %ymm1
	vpblendd	$48, %ymm5, %ymm4, %ymm4
	vpblendd	$48, %ymm7, %ymm11, %ymm11
	vpxor	%ymm3, %ymm2, %ymm2
	vpblendd	$192, %ymm7, %ymm4, %ymm4
	vpblendd	$192, %ymm10, %ymm11, %ymm11
	vpandn	%ymm11, %ymm4, %ymm4
	vpxor	%ymm9, %ymm4, %ymm12
	vpermq	$30, %ymm8, %ymm4
	vpblendd	$48, %ymm6, %ymm4, %ymm4
	vpermq	$57, %ymm8, %ymm11
	vpblendd	$192, %ymm6, %ymm11, %ymm11
	vpandn	%ymm4, %ymm11, %ymm11
	vpblendd	$12, %ymm3, %ymm7, %ymm4
	vpblendd	$12, %ymm7, %ymm9, %ymm13
	vpblendd	$48, %ymm9, %ymm4, %ymm4
	vpblendd	$48, %ymm5, %ymm13, %ymm13
	vpblendd	$192, %ymm5, %ymm4, %ymm4
	vpblendd	$192, %ymm3, %ymm13, %ymm13
	vpandn	%ymm13, %ymm4, %ymm4
	vpxor	%ymm10, %ymm4, %ymm4
	vpermq	$0, %ymm0, %ymm13
	vpermq	$27, %ymm1, %ymm0
	vpermq	$141, %ymm2, %ymm1
	vpermq	$114, %ymm12, %ymm2
	vpblendd	$12, %ymm5, %ymm9, %ymm12
	vpblendd	$12, %ymm9, %ymm3, %ymm9
	vpblendd	$48, %ymm3, %ymm12, %ymm3
	vpblendd	$48, %ymm10, %ymm9, %ymm9
	vpblendd	$192, %ymm10, %ymm3, %ymm3
	vpblendd	$192, %ymm5, %ymm9, %ymm5
	vpandn	%ymm5, %ymm3, %ymm5
	vpxor	%ymm13, %ymm6, %ymm6
	vpxor	%ymm8, %ymm11, %ymm3
	vpxor	%ymm7, %ymm5, %ymm5
	vpxor	(%r10,%r11), %ymm6, %ymm6
	addq	$32, %r11
	decq	%r12
	jne 	L_keccak1600_avx2$17
L_keccak1600_avx2$15:
	cmpq	%r9, %rcx
	jnb 	L_keccak1600_avx2$16
	vpxor	%ymm7, %ymm7, %ymm7
	vmovdqu	%ymm7, (%rsp)
	vmovdqu	%ymm7, 32(%rsp)
	vmovdqu	%ymm7, 64(%rsp)
	vmovdqu	%ymm7, 96(%rsp)
	vmovdqu	%ymm7, 128(%rsp)
	vmovdqu	%ymm7, 160(%rsp)
	vmovdqu	%ymm7, 192(%rsp)
	movq	%rcx, %r10
	shrq	$3, %r10
	movq	$0, %r11
	jmp 	L_keccak1600_avx2$13
L_keccak1600_avx2$14:
	movq	(%rdx,%r11,8), %rbx
	movq	(%rax,%r11,8), %rbp
	movq	%rbx, (%rsp,%rbp,8)
	incq	%r11
L_keccak1600_avx2$13:
	cmpq	%r10, %r11
	jb  	L_keccak1600_avx2$14
	movq	(%rax,%r11,8), %r10
	shlq	$3, %r10
	shlq	$3, %r11
	jmp 	L_keccak1600_avx2$11
L_keccak1600_avx2$12:
	movb	(%rdx,%r11), %bl
	movb	%bl, (%rsp,%r10)
	incq	%r11
	incq	%r10
L_keccak1600_avx2$11:
	cmpq	%rcx, %r11
	jb  	L_keccak1600_avx2$12
	movb	%r8b, (%rsp,%r10)
	movq	%r9, %rcx
	addq	$-1, %rcx
	shrq	$3, %rcx
	movq	(%rax,%rcx,8), %rax
	shlq	$3, %rax
	movq	%r9, %rcx
	addq	$-1, %rcx
	andq	$7, %rcx
	addq	%rcx, %rax
	xorb	$128, (%rsp,%rax)
	movq	(%rsp), %rax
	movq	%rax, 8(%rsp)
	movq	%rax, 16(%rsp)
	movq	%rax, 24(%rsp)
	vpxor	(%rsp), %ymm6, %ymm6
	vpxor	32(%rsp), %ymm3, %ymm3
	vpxor	64(%rsp), %ymm4, %ymm4
	vpxor	96(%rsp), %ymm0, %ymm0
	vpxor	128(%rsp), %ymm5, %ymm5
	vpxor	160(%rsp), %ymm1, %ymm1
	vpxor	192(%rsp), %ymm2, %ymm2
	leaq	glob_data + 1152(%rip), %rax
	jmp 	L_keccak1600_avx2$6
L_keccak1600_avx2$7:
	leaq	glob_data + 384(%rip), %rcx
	movq	$0, %rdx
	leaq	glob_data + 192(%rip), %r8
	leaq	glob_data + 0(%rip), %r10
	movq	$24, %r11
L_keccak1600_avx2$10:
	vpshufd	$78, %ymm4, %ymm8
	vpxor	%ymm0, %ymm1, %ymm7
	vpxor	%ymm2, %ymm5, %ymm9
	vpxor	%ymm3, %ymm7, %ymm7
	vpxor	%ymm9, %ymm7, %ymm10
	vpermq	$147, %ymm10, %ymm7
	vpxor	%ymm4, %ymm8, %ymm8
	vpermq	$78, %ymm8, %ymm9
	vpsrlq	$63, %ymm10, %ymm11
	vpaddq	%ymm10, %ymm10, %ymm10
	vpor	%ymm10, %ymm11, %ymm11
	vpermq	$57, %ymm11, %ymm10
	vpxor	%ymm7, %ymm11, %ymm11
	vpermq	$0, %ymm11, %ymm11
	vpxor	%ymm6, %ymm8, %ymm8
	vpxor	%ymm9, %ymm8, %ymm8
	vpsrlq	$63, %ymm8, %ymm9
	vpaddq	%ymm8, %ymm8, %ymm12
	vpor	%ymm9, %ymm12, %ymm9
	vpxor	%ymm11, %ymm4, %ymm4
	vpxor	%ymm11, %ymm6, %ymm6
	vpblendd	$192, %ymm9, %ymm10, %ymm9
	vpblendd	$3, %ymm8, %ymm7, %ymm7
	vpxor	%ymm7, %ymm9, %ymm9
	vpsllvq	(%r8), %ymm4, %ymm7
	vpsrlvq	(%r10), %ymm4, %ymm4
	vpor	%ymm7, %ymm4, %ymm4
	vpxor	%ymm9, %ymm0, %ymm0
	vpsllvq	64(%r8), %ymm0, %ymm7
	vpsrlvq	64(%r10), %ymm0, %ymm0
	vpor	%ymm7, %ymm0, %ymm0
	vpxor	%ymm9, %ymm5, %ymm5
	vpsllvq	96(%r8), %ymm5, %ymm7
	vpsrlvq	96(%r10), %ymm5, %ymm5
	vpor	%ymm7, %ymm5, %ymm10
	vpxor	%ymm9, %ymm1, %ymm1
	vpsllvq	128(%r8), %ymm1, %ymm5
	vpsrlvq	128(%r10), %ymm1, %ymm1
	vpor	%ymm5, %ymm1, %ymm1
	vpxor	%ymm9, %ymm2, %ymm2
	vpermq	$141, %ymm4, %ymm5
	vpermq	$141, %ymm0, %ymm7
	vpsllvq	160(%r8), %ymm2, %ymm0
	vpsrlvq	160(%r10), %ymm2, %ymm2
	vpor	%ymm0, %ymm2, %ymm8
	vpxor	%ymm9, %ymm3, %ymm0
	vpermq	$27, %ymm10, %ymm3
	vpermq	$114, %ymm1, %ymm9
	vpsllvq	32(%r8), %ymm0, %ymm1
	vpsrlvq	32(%r10), %ymm0, %ymm0
	vpor	%ymm1, %ymm0, %ymm10
	vpsrldq	$8, %ymm8, %ymm0
	vpandn	%ymm0, %ymm8, %ymm0
	vpblendd	$12, %ymm9, %ymm10, %ymm1
	vpblendd	$12, %ymm10, %ymm7, %ymm2
	vpblendd	$12, %ymm7, %ymm5, %ymm4
	vpblendd	$12, %ymm5, %ymm10, %ymm11
	vpblendd	$48, %ymm7, %ymm1, %ymm1
	vpblendd	$48, %ymm3, %ymm2, %ymm2
	vpblendd	$48, %ymm10, %ymm4, %ymm4
	vpblendd	$48, %ymm9, %ymm11, %ymm11
	vpblendd	$192, %ymm3, %ymm1, %ymm1
	vpblendd	$192, %ymm9, %ymm2, %ymm2
	vpblendd	$192, %ymm9, %ymm4, %ymm4
	vpblendd	$192, %ymm7, %ymm11, %ymm11
	vpandn	%ymm2, %ymm1, %ymm1
	vpandn	%ymm11, %ymm4, %ymm2
	vpblendd	$12, %ymm10, %ymm3, %ymm4
	vpblendd	$12, %ymm3, %ymm5, %ymm11
	vpxor	%ymm5, %ymm1, %ymm1
	vpblendd	$48, %ymm5, %ymm4, %ymm4
	vpblendd	$48, %ymm7, %ymm11, %ymm11
	vpxor	%ymm3, %ymm2, %ymm2
	vpblendd	$192, %ymm7, %ymm4, %ymm4
	vpblendd	$192, %ymm10, %ymm11, %ymm11
	vpandn	%ymm11, %ymm4, %ymm4
	vpxor	%ymm9, %ymm4, %ymm12
	vpermq	$30, %ymm8, %ymm4
	vpblendd	$48, %ymm6, %ymm4, %ymm4
	vpermq	$57, %ymm8, %ymm11
	vpblendd	$192, %ymm6, %ymm11, %ymm11
	vpandn	%ymm4, %ymm11, %ymm11
	vpblendd	$12, %ymm3, %ymm7, %ymm4
	vpblendd	$12, %ymm7, %ymm9, %ymm13
	vpblendd	$48, %ymm9, %ymm4, %ymm4
	vpblendd	$48, %ymm5, %ymm13, %ymm13
	vpblendd	$192, %ymm5, %ymm4, %ymm4
	vpblendd	$192, %ymm3, %ymm13, %ymm13
	vpandn	%ymm13, %ymm4, %ymm4
	vpxor	%ymm10, %ymm4, %ymm4
	vpermq	$0, %ymm0, %ymm13
	vpermq	$27, %ymm1, %ymm0
	vpermq	$141, %ymm2, %ymm1
	vpermq	$114, %ymm12, %ymm2
	vpblendd	$12, %ymm5, %ymm9, %ymm12
	vpblendd	$12, %ymm9, %ymm3, %ymm9
	vpblendd	$48, %ymm3, %ymm12, %ymm3
	vpblendd	$48, %ymm10, %ymm9, %ymm9
	vpblendd	$192, %ymm10, %ymm3, %ymm3
	vpblendd	$192, %ymm5, %ymm9, %ymm5
	vpandn	%ymm5, %ymm3, %ymm5
	vpxor	%ymm13, %ymm6, %ymm6
	vpxor	%ymm8, %ymm11, %ymm3
	vpxor	%ymm7, %ymm5, %ymm5
	vpxor	(%rcx,%rdx), %ymm6, %ymm6
	addq	$32, %rdx
	decq	%r11
	jne 	L_keccak1600_avx2$10
	vmovdqu	%ymm6, (%rsp)
	vmovdqu	%ymm3, 32(%rsp)
	vmovdqu	%ymm4, 64(%rsp)
	vmovdqu	%ymm0, 96(%rsp)
	vmovdqu	%ymm5, 128(%rsp)
	vmovdqu	%ymm1, 160(%rsp)
	vmovdqu	%ymm2, 192(%rsp)
	movq	%r9, %rcx
	shrq	$3, %rcx
	movq	$0, %rdx
	jmp 	L_keccak1600_avx2$8
L_keccak1600_avx2$9:
	movq	(%rax,%rdx,8), %r8
	movq	(%rsp,%r8,8), %r8
	movq	%r8, (%rdi,%rdx,8)
	incq	%rdx
L_keccak1600_avx2$8:
	cmpq	%rcx, %rdx
	jb  	L_keccak1600_avx2$9
	addq	%r9, %rdi
	subq	%r9, %rsi
L_keccak1600_avx2$6:
	cmpq	%r9, %rsi
	jnbe	L_keccak1600_avx2$7
	leaq	glob_data + 384(%rip), %rcx
	movq	$0, %rdx
	leaq	glob_data + 192(%rip), %r8
	leaq	glob_data + 0(%rip), %r9
	movq	$24, %r10
L_keccak1600_avx2$5:
	vpshufd	$78, %ymm4, %ymm8
	vpxor	%ymm0, %ymm1, %ymm7
	vpxor	%ymm2, %ymm5, %ymm9
	vpxor	%ymm3, %ymm7, %ymm7
	vpxor	%ymm9, %ymm7, %ymm10
	vpermq	$147, %ymm10, %ymm7
	vpxor	%ymm4, %ymm8, %ymm8
	vpermq	$78, %ymm8, %ymm9
	vpsrlq	$63, %ymm10, %ymm11
	vpaddq	%ymm10, %ymm10, %ymm10
	vpor	%ymm10, %ymm11, %ymm11
	vpermq	$57, %ymm11, %ymm10
	vpxor	%ymm7, %ymm11, %ymm11
	vpermq	$0, %ymm11, %ymm11
	vpxor	%ymm6, %ymm8, %ymm8
	vpxor	%ymm9, %ymm8, %ymm8
	vpsrlq	$63, %ymm8, %ymm9
	vpaddq	%ymm8, %ymm8, %ymm12
	vpor	%ymm9, %ymm12, %ymm9
	vpxor	%ymm11, %ymm4, %ymm4
	vpxor	%ymm11, %ymm6, %ymm6
	vpblendd	$192, %ymm9, %ymm10, %ymm9
	vpblendd	$3, %ymm8, %ymm7, %ymm7
	vpxor	%ymm7, %ymm9, %ymm9
	vpsllvq	(%r8), %ymm4, %ymm7
	vpsrlvq	(%r9), %ymm4, %ymm4
	vpor	%ymm7, %ymm4, %ymm4
	vpxor	%ymm9, %ymm0, %ymm0
	vpsllvq	64(%r8), %ymm0, %ymm7
	vpsrlvq	64(%r9), %ymm0, %ymm0
	vpor	%ymm7, %ymm0, %ymm0
	vpxor	%ymm9, %ymm5, %ymm5
	vpsllvq	96(%r8), %ymm5, %ymm7
	vpsrlvq	96(%r9), %ymm5, %ymm5
	vpor	%ymm7, %ymm5, %ymm10
	vpxor	%ymm9, %ymm1, %ymm1
	vpsllvq	128(%r8), %ymm1, %ymm5
	vpsrlvq	128(%r9), %ymm1, %ymm1
	vpor	%ymm5, %ymm1, %ymm1
	vpxor	%ymm9, %ymm2, %ymm2
	vpermq	$141, %ymm4, %ymm5
	vpermq	$141, %ymm0, %ymm7
	vpsllvq	160(%r8), %ymm2, %ymm0
	vpsrlvq	160(%r9), %ymm2, %ymm2
	vpor	%ymm0, %ymm2, %ymm8
	vpxor	%ymm9, %ymm3, %ymm0
	vpermq	$27, %ymm10, %ymm3
	vpermq	$114, %ymm1, %ymm9
	vpsllvq	32(%r8), %ymm0, %ymm1
	vpsrlvq	32(%r9), %ymm0, %ymm0
	vpor	%ymm1, %ymm0, %ymm10
	vpsrldq	$8, %ymm8, %ymm0
	vpandn	%ymm0, %ymm8, %ymm0
	vpblendd	$12, %ymm9, %ymm10, %ymm1
	vpblendd	$12, %ymm10, %ymm7, %ymm2
	vpblendd	$12, %ymm7, %ymm5, %ymm4
	vpblendd	$12, %ymm5, %ymm10, %ymm11
	vpblendd	$48, %ymm7, %ymm1, %ymm1
	vpblendd	$48, %ymm3, %ymm2, %ymm2
	vpblendd	$48, %ymm10, %ymm4, %ymm4
	vpblendd	$48, %ymm9, %ymm11, %ymm11
	vpblendd	$192, %ymm3, %ymm1, %ymm1
	vpblendd	$192, %ymm9, %ymm2, %ymm2
	vpblendd	$192, %ymm9, %ymm4, %ymm4
	vpblendd	$192, %ymm7, %ymm11, %ymm11
	vpandn	%ymm2, %ymm1, %ymm1
	vpandn	%ymm11, %ymm4, %ymm2
	vpblendd	$12, %ymm10, %ymm3, %ymm4
	vpblendd	$12, %ymm3, %ymm5, %ymm11
	vpxor	%ymm5, %ymm1, %ymm1
	vpblendd	$48, %ymm5, %ymm4, %ymm4
	vpblendd	$48, %ymm7, %ymm11, %ymm11
	vpxor	%ymm3, %ymm2, %ymm2
	vpblendd	$192, %ymm7, %ymm4, %ymm4
	vpblendd	$192, %ymm10, %ymm11, %ymm11
	vpandn	%ymm11, %ymm4, %ymm4
	vpxor	%ymm9, %ymm4, %ymm12
	vpermq	$30, %ymm8, %ymm4
	vpblendd	$48, %ymm6, %ymm4, %ymm4
	vpermq	$57, %ymm8, %ymm11
	vpblendd	$192, %ymm6, %ymm11, %ymm11
	vpandn	%ymm4, %ymm11, %ymm11
	vpblendd	$12, %ymm3, %ymm7, %ymm4
	vpblendd	$12, %ymm7, %ymm9, %ymm13
	vpblendd	$48, %ymm9, %ymm4, %ymm4
	vpblendd	$48, %ymm5, %ymm13, %ymm13
	vpblendd	$192, %ymm5, %ymm4, %ymm4
	vpblendd	$192, %ymm3, %ymm13, %ymm13
	vpandn	%ymm13, %ymm4, %ymm4
	vpxor	%ymm10, %ymm4, %ymm4
	vpermq	$0, %ymm0, %ymm13
	vpermq	$27, %ymm1, %ymm0
	vpermq	$141, %ymm2, %ymm1
	vpermq	$114, %ymm12, %ymm2
	vpblendd	$12, %ymm5, %ymm9, %ymm12
	vpblendd	$12, %ymm9, %ymm3, %ymm9
	vpblendd	$48, %ymm3, %ymm12, %ymm3
	vpblendd	$48, %ymm10, %ymm9, %ymm9
	vpblendd	$192, %ymm10, %ymm3, %ymm3
	vpblendd	$192, %ymm5, %ymm9, %ymm5
	vpandn	%ymm5, %ymm3, %ymm5
	vpxor	%ymm13, %ymm6, %ymm6
	vpxor	%ymm8, %ymm11, %ymm3
	vpxor	%ymm7, %ymm5, %ymm5
	vpxor	(%rcx,%rdx), %ymm6, %ymm6
	addq	$32, %rdx
	decq	%r10
	jne 	L_keccak1600_avx2$5
	vmovdqu	%ymm6, (%rsp)
	vmovdqu	%ymm3, 32(%rsp)
	vmovdqu	%ymm4, 64(%rsp)
	vmovdqu	%ymm0, 96(%rsp)
	vmovdqu	%ymm5, 128(%rsp)
	vmovdqu	%ymm1, 160(%rsp)
	vmovdqu	%ymm2, 192(%rsp)
	movq	%rsi, %rcx
	shrq	$3, %rcx
	movq	$0, %rdx
	jmp 	L_keccak1600_avx2$3
L_keccak1600_avx2$4:
	movq	(%rax,%rdx,8), %r8
	movq	(%rsp,%r8,8), %r8
	movq	%r8, (%rdi,%rdx,8)
	incq	%rdx
L_keccak1600_avx2$3:
	cmpq	%rcx, %rdx
	jb  	L_keccak1600_avx2$4
	movq	(%rax,%rdx,8), %rax
	shlq	$3, %rdx
	shlq	$3, %rax
	jmp 	L_keccak1600_avx2$1
L_keccak1600_avx2$2:
	movb	(%rsp,%rax), %cl
	movb	%cl, (%rdi,%rdx)
	incq	%rdx
	incq	%rax
L_keccak1600_avx2$1:
	cmpq	%rsi, %rdx
	jb  	L_keccak1600_avx2$2
	movq	224(%rsp), %rbx
	movq	232(%rsp), %rbp
	movq	240(%rsp), %r12
	movq	248(%rsp), %rsp
	ret
	.data
	.p2align	5
_glob_data:
glob_data:
G$KECCAK_RHOTATES_RIGHT:
	.byte	61
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	46
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	28
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	23
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	63
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	36
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	37
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	19
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	58
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	54
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	56
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	62
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	49
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	39
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	44
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	43
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	50
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
G$KECCAK_RHOTATES_LEFT:
	.byte	3
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	36
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	41
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	62
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	28
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	45
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	56
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	39
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	10
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	61
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	55
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	44
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	43
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	14
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
G$KECCAK_IOTAS:
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.byte	-126
	.byte	-128
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
	.byte	-118
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-118
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
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
	.byte	0
	.byte	-128
	.byte	0
	.byte	-128
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
	.byte	-117
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-117
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.byte	1
	.byte	0
	.byte	0
	.byte	-128
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
	.byte	-127
	.byte	-128
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
	.byte	9
	.byte	-128
	.byte	0
	.byte	0
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
	.byte	-118
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-118
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.byte	-120
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
	.byte	9
	.byte	-128
	.byte	0
	.byte	-128
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
	.byte	10
	.byte	0
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
	.byte	-128
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
	.byte	-117
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	-117
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
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
	.byte	-119
	.byte	-128
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
	.byte	3
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
	.byte	2
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
	.byte	-128
	.byte	0
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
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	10
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
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
	.byte	10
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	10
	.byte	0
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
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
	.byte	-127
	.byte	-128
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
	.byte	-128
	.byte	-128
	.byte	0
	.byte	0
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
	.byte	1
	.byte	0
	.byte	0
	.byte	-128
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
	.byte	8
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	8
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
	.byte	8
	.byte	-128
	.byte	0
	.byte	-128
	.byte	0
	.byte	0
	.byte	0
	.byte	-128
G$KECCAK_A_JAGGED:
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	5
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	6
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	7
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	10
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	24
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	13
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	18
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	23
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	16
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	22
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	11
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	12
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	21
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	26
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	19
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	9
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	20
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	17
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	14
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	27
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
