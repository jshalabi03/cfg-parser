	.text
	.file	"index.cpp"
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	wzr, [sp, #12]
	mov	w8, #3
	str	w8, [sp, #8]
	b	.LBB0_1
.LBB0_1:                                // =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	subs	w8, w8, #5
	b.ge	.LBB0_3
	b	.LBB0_2
.LBB0_2:                                //   in Loop: Header=BB0_1 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #8]
	b	.LBB0_1
.LBB0_3:
	ldr	w8, [sp, #8]
	subs	w8, w8, #5
	b.ne	.LBB0_5
	b	.LBB0_4
.LBB0_4:
	str	wzr, [sp, #8]
	b	.LBB0_5
.LBB0_5:
	mov	w0, wzr
	add	sp, sp, #16
	ret
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        // -- End function
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
