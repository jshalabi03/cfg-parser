	.text
	.file	"index.cpp"
	.globl	_Z2f2i                          // -- Begin function _Z2f2i
	.p2align	2
	.type	_Z2f2i,@function
_Z2f2i:                                 // @_Z2f2i
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	ldr	w8, [sp, #12]
	add	w0, w8, #2
	add	sp, sp, #16
	ret
.Lfunc_end0:
	.size	_Z2f2i, .Lfunc_end0-_Z2f2i
	.cfi_endproc
                                        // -- End function
	.globl	_Z2f1i                          // -- Begin function _Z2f1i
	.p2align	2
	.type	_Z2f1i,@function
_Z2f1i:                                 // @_Z2f1i
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             // 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-4]
	mov	w0, #2
	bl	_Z2f2i
	ldur	w8, [x29, #-4]
	add	w8, w0, w8
	add	w0, w8, #1
	ldp	x29, x30, [sp, #16]             // 16-byte Folded Reload
	add	sp, sp, #32
	ret
.Lfunc_end1:
	.size	_Z2f1i, .Lfunc_end1-_Z2f1i
	.cfi_endproc
                                        // -- End function
	.globl	_Z2f0i                          // -- Begin function _Z2f0i
	.p2align	2
	.type	_Z2f0i,@function
_Z2f0i:                                 // @_Z2f0i
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             // 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	w0, [x29, #-4]
	mov	w0, #1
	bl	_Z2f1i
	str	w0, [sp, #8]                    // 4-byte Folded Spill
	mov	w0, #2
	bl	_Z2f2i
	mov	w8, w0
	ldr	w0, [sp, #8]                    // 4-byte Folded Reload
	add	w0, w0, w8
	ldp	x29, x30, [sp, #16]             // 16-byte Folded Reload
	add	sp, sp, #32
	ret
.Lfunc_end2:
	.size	_Z2f0i, .Lfunc_end2-_Z2f0i
	.cfi_endproc
                                        // -- End function
	.globl	_Z7pointedi                     // -- Begin function _Z7pointedi
	.p2align	2
	.type	_Z7pointedi,@function
_Z7pointedi:                            // @_Z7pointedi
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	ldr	w0, [sp, #12]
	add	sp, sp, #16
	ret
.Lfunc_end3:
	.size	_Z7pointedi, .Lfunc_end3-_Z7pointedi
	.cfi_endproc
                                        // -- End function
	.globl	_Z10not_calledi                 // -- Begin function _Z10not_calledi
	.p2align	2
	.type	_Z10not_calledi,@function
_Z10not_calledi:                        // @_Z10not_calledi
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	w0, [sp, #12]
	mov	w0, wzr
	add	sp, sp, #16
	ret
.Lfunc_end4:
	.size	_Z10not_calledi, .Lfunc_end4-_Z10not_calledi
	.cfi_endproc
                                        // -- End function
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             // 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	stur	w0, [x29, #-8]
	str	x1, [sp, #16]
	mov	w0, #1
	str	w0, [sp, #4]                    // 4-byte Folded Spill
	bl	_Z2f0i
	ldr	w0, [sp, #4]                    // 4-byte Folded Reload
	bl	_Z2f1i
	adrp	x8, _Z7pointedi
	add	x8, x8, :lo12:_Z7pointedi
	str	x8, [sp, #8]
	ldur	w8, [x29, #-8]
	subs	w8, w8, #1
	b.ne	.LBB5_2
	b	.LBB5_1
.LBB5_1:
	ldr	x8, [sp, #8]
	mov	w0, #1
	blr	x8
	b	.LBB5_2
.LBB5_2:
	ldur	w8, [x29, #-8]
	subs	w8, w8, #2
	b.ne	.LBB5_4
	b	.LBB5_3
.LBB5_3:
	mov	w0, #1
	bl	_Z10not_calledi
	b	.LBB5_4
.LBB5_4:
	mov	w0, wzr
	ldp	x29, x30, [sp, #32]             // 16-byte Folded Reload
	add	sp, sp, #48
	ret
.Lfunc_end5:
	.size	main, .Lfunc_end5-main
	.cfi_endproc
                                        // -- End function
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym _Z2f2i
	.addrsig_sym _Z2f1i
	.addrsig_sym _Z2f0i
	.addrsig_sym _Z7pointedi
	.addrsig_sym _Z10not_calledi
