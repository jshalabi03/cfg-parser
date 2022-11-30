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
	mov	w8, #1
	str	w8, [sp, #8]
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #4]
	ldr	w8, [sp, #8]
	ldr w9, [sp, #4]
	subs	w8, w8, w9
	b.ge	.LBB0_2
	b	.LBB0_1
.LBB0_1:
	ldr	w8, [sp, #4]
	str	w8, [sp, #8]
	b	.LBB0_3
.LBB0_2:
	ldr	w8, [sp, #8]
	str	w8, [sp, #4]
	ldr	w8, [sp, #8]
	lsl	w8, w8, #1
	str	w8, [sp, #8]
	b	.LBB0_3
.LBB0_3:
	ldr	w8, [sp, #8]
	ldr	w9, [sp, #4]
	add	w8, w8, w9
	str	w8, [sp]
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
