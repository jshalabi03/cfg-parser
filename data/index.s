	.text
	.file	"index.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	2                               // -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  // @__cxx_global_var_init
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #32
	stp	x29, x30, [sp, #16]             // 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	adrp	x0, _ZStL8__ioinit
	add	x0, x0, :lo12:_ZStL8__ioinit
	str	x0, [sp, #8]                    // 8-byte Folded Spill
	bl	_ZNSt8ios_base4InitC1Ev
	ldr	x1, [sp, #8]                    // 8-byte Folded Reload
	adrp	x0, :got:_ZNSt8ios_base4InitD1Ev
	ldr	x0, [x0, :got_lo12:_ZNSt8ios_base4InitD1Ev]
	adrp	x2, __dso_handle
	add	x2, x2, :lo12:__dso_handle
	bl	__cxa_atexit
	ldp	x29, x30, [sp, #16]             // 16-byte Folded Reload
	add	sp, sp, #32
	ret
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        // -- End function
	.text
	.globl	_Z9partitionPiii                // -- Begin function _Z9partitionPiii
	.p2align	2
	.type	_Z9partitionPiii,@function
_Z9partitionPiii:                       // @_Z9partitionPiii
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]             // 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	stur	w2, [x29, #-16]
	ldur	x8, [x29, #-8]
	ldursw	x9, [x29, #-12]
	ldr	w8, [x8, x9, lsl #2]
	stur	w8, [x29, #-20]
	str	wzr, [sp, #24]
	ldur	w8, [x29, #-12]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	.LBB1_1
.LBB1_1:                                // =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #20]
	ldur	w9, [x29, #-16]
	subs	w8, w8, w9
	b.gt	.LBB1_6
	b	.LBB1_2
.LBB1_2:                                //   in Loop: Header=BB1_1 Depth=1
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #20]
	ldr	w8, [x8, x9, lsl #2]
	ldur	w9, [x29, #-20]
	subs	w8, w8, w9
	b.gt	.LBB1_4
	b	.LBB1_3
.LBB1_3:                                //   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #24]
	add	w8, w8, #1
	str	w8, [sp, #24]
	b	.LBB1_4
.LBB1_4:                                //   in Loop: Header=BB1_1 Depth=1
	b	.LBB1_5
.LBB1_5:                                //   in Loop: Header=BB1_1 Depth=1
	ldr	w8, [sp, #20]
	add	w8, w8, #1
	str	w8, [sp, #20]
	b	.LBB1_1
.LBB1_6:
	ldur	w8, [x29, #-12]
	ldr	w9, [sp, #24]
	add	w8, w8, w9
	str	w8, [sp, #16]
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #16]
	add	x0, x8, x9, lsl #2
	ldur	x8, [x29, #-8]
	ldursw	x9, [x29, #-12]
	add	x1, x8, x9, lsl #2
	bl	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	ldur	w8, [x29, #-12]
	str	w8, [sp, #12]
	ldur	w8, [x29, #-16]
	str	w8, [sp, #8]
	b	.LBB1_7
.LBB1_7:                                // =>This Loop Header: Depth=1
                                        //     Child Loop BB1_11 Depth 2
                                        //     Child Loop BB1_14 Depth 2
	ldr	w9, [sp, #12]
	ldr	w10, [sp, #16]
	mov	w8, #0
	subs	w9, w9, w10
	str	w8, [sp, #4]                    // 4-byte Folded Spill
	b.ge	.LBB1_9
	b	.LBB1_8
.LBB1_8:                                //   in Loop: Header=BB1_7 Depth=1
	ldr	w8, [sp, #8]
	ldr	w9, [sp, #16]
	subs	w8, w8, w9
	cset	w8, gt
	str	w8, [sp, #4]                    // 4-byte Folded Spill
	b	.LBB1_9
.LBB1_9:                                //   in Loop: Header=BB1_7 Depth=1
	ldr	w8, [sp, #4]                    // 4-byte Folded Reload
	tbz	w8, #0, .LBB1_20
	b	.LBB1_10
.LBB1_10:                               //   in Loop: Header=BB1_7 Depth=1
	b	.LBB1_11
.LBB1_11:                               //   Parent Loop BB1_7 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #12]
	ldr	w8, [x8, x9, lsl #2]
	ldur	w9, [x29, #-20]
	subs	w8, w8, w9
	b.gt	.LBB1_13
	b	.LBB1_12
.LBB1_12:                               //   in Loop: Header=BB1_11 Depth=2
	ldr	w8, [sp, #12]
	add	w8, w8, #1
	str	w8, [sp, #12]
	b	.LBB1_11
.LBB1_13:                               //   in Loop: Header=BB1_7 Depth=1
	b	.LBB1_14
.LBB1_14:                               //   Parent Loop BB1_7 Depth=1
                                        // =>  This Inner Loop Header: Depth=2
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #8]
	ldr	w8, [x8, x9, lsl #2]
	ldur	w9, [x29, #-20]
	subs	w8, w8, w9
	b.le	.LBB1_16
	b	.LBB1_15
.LBB1_15:                               //   in Loop: Header=BB1_14 Depth=2
	ldr	w8, [sp, #8]
	subs	w8, w8, #1
	str	w8, [sp, #8]
	b	.LBB1_14
.LBB1_16:                               //   in Loop: Header=BB1_7 Depth=1
	ldr	w8, [sp, #12]
	ldr	w9, [sp, #16]
	subs	w8, w8, w9
	b.ge	.LBB1_19
	b	.LBB1_17
.LBB1_17:                               //   in Loop: Header=BB1_7 Depth=1
	ldr	w8, [sp, #8]
	ldr	w9, [sp, #16]
	subs	w8, w8, w9
	b.le	.LBB1_19
	b	.LBB1_18
.LBB1_18:                               //   in Loop: Header=BB1_7 Depth=1
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #12]
	mov	w10, w9
	add	w10, w10, #1
	str	w10, [sp, #12]
	add	x0, x8, x9, lsl #2
	ldur	x8, [x29, #-8]
	ldrsw	x9, [sp, #8]
	mov	w10, w9
	subs	w10, w10, #1
	str	w10, [sp, #8]
	add	x1, x8, x9, lsl #2
	bl	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	b	.LBB1_19
.LBB1_19:                               //   in Loop: Header=BB1_7 Depth=1
	b	.LBB1_7
.LBB1_20:
	ldr	w0, [sp, #16]
	ldp	x29, x30, [sp, #48]             // 16-byte Folded Reload
	add	sp, sp, #64
	ret
.Lfunc_end1:
	.size	_Z9partitionPiii, .Lfunc_end1-_Z9partitionPiii
	.cfi_endproc
                                        // -- End function
	.section	.text._ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,"axG",@progbits,_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,comdat
	.weak	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_ // -- Begin function _ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.p2align	2
	.type	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_,@function
_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_: // @_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             // 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	str	x1, [sp, #16]
	ldur	x0, [x29, #-8]
	bl	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	ldr	w8, [x0]
	add	x9, sp, #12
	str	x9, [sp]                        // 8-byte Folded Spill
	str	w8, [sp, #12]
	ldr	x0, [sp, #16]
	bl	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	mov	x8, x0
	ldr	x0, [sp]                        // 8-byte Folded Reload
	ldr	w8, [x8]
	ldur	x9, [x29, #-8]
	str	w8, [x9]
	bl	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	ldr	w8, [x0]
	ldr	x9, [sp, #16]
	str	w8, [x9]
	ldp	x29, x30, [sp, #32]             // 16-byte Folded Reload
	add	sp, sp, #48
	ret
.Lfunc_end2:
	.size	_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_, .Lfunc_end2-_ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.cfi_endproc
                                        // -- End function
	.text
	.globl	_Z9quickSortPiii                // -- Begin function _Z9quickSortPiii
	.p2align	2
	.type	_Z9quickSortPiii,@function
_Z9quickSortPiii:                       // @_Z9quickSortPiii
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             // 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	w1, [x29, #-12]
	str	w2, [sp, #16]
	ldur	w8, [x29, #-12]
	ldr	w9, [sp, #16]
	subs	w8, w8, w9
	b.lt	.LBB3_2
	b	.LBB3_1
.LBB3_1:
	b	.LBB3_3
.LBB3_2:
	ldur	x0, [x29, #-8]
	ldur	w1, [x29, #-12]
	ldr	w2, [sp, #16]
	bl	_Z9partitionPiii
	str	w0, [sp, #12]
	ldur	x0, [x29, #-8]
	ldur	w1, [x29, #-12]
	ldr	w8, [sp, #12]
	subs	w2, w8, #1
	bl	_Z9quickSortPiii
	ldur	x0, [x29, #-8]
	ldr	w8, [sp, #12]
	add	w1, w8, #1
	ldr	w2, [sp, #16]
	bl	_Z9quickSortPiii
	b	.LBB3_3
.LBB3_3:
	ldp	x29, x30, [sp, #32]             // 16-byte Folded Reload
	add	sp, sp, #48
	ret
.Lfunc_end3:
	.size	_Z9quickSortPiii, .Lfunc_end3-_Z9quickSortPiii
	.cfi_endproc
                                        // -- End function
	.globl	main                            // -- Begin function main
	.p2align	2
	.type	main,@function
main:                                   // @main
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]             // 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	mov	w1, wzr
	stur	wzr, [x29, #-4]
	adrp	x8, .L__const.main.arr
	add	x8, x8, :lo12:.L__const.main.arr
	ldr	q0, [x8]
	add	x0, sp, #16
	str	q0, [sp, #16]
	ldr	x8, [x8, #16]
	str	x8, [sp, #32]
	mov	w8, #6
	str	w8, [sp, #12]
	ldr	w8, [sp, #12]
	subs	w2, w8, #1
	bl	_Z9quickSortPiii
	str	wzr, [sp, #8]
	b	.LBB4_1
.LBB4_1:                                // =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #8]
	ldr	w9, [sp, #12]
	subs	w8, w8, w9
	b.ge	.LBB4_4
	b	.LBB4_2
.LBB4_2:                                //   in Loop: Header=BB4_1 Depth=1
	ldrsw	x9, [sp, #8]
	add	x8, sp, #16
	ldr	w1, [x8, x9, lsl #2]
	adrp	x0, :got:_ZSt4cout
	ldr	x0, [x0, :got_lo12:_ZSt4cout]
	bl	_ZNSolsEi
	adrp	x1, .L.str
	add	x1, x1, :lo12:.L.str
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	b	.LBB4_3
.LBB4_3:                                //   in Loop: Header=BB4_1 Depth=1
	ldr	w8, [sp, #8]
	add	w8, w8, #1
	str	w8, [sp, #8]
	b	.LBB4_1
.LBB4_4:
	mov	w0, wzr
	ldp	x29, x30, [sp, #48]             // 16-byte Folded Reload
	add	sp, sp, #64
	ret
.Lfunc_end4:
	.size	main, .Lfunc_end4-main
	.cfi_endproc
                                        // -- End function
	.section	.text._ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,"axG",@progbits,_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,comdat
	.weak	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_ // -- Begin function _ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.p2align	2
	.type	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,@function
_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_: // @_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.cfi_startproc
// %bb.0:
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	str	x0, [sp, #8]
	ldr	x0, [sp, #8]
	add	sp, sp, #16
	ret
.Lfunc_end5:
	.size	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_, .Lfunc_end5-_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.cfi_endproc
                                        // -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	2                               // -- Begin function _GLOBAL__sub_I_index.cpp
	.type	_GLOBAL__sub_I_index.cpp,@function
_GLOBAL__sub_I_index.cpp:               // @_GLOBAL__sub_I_index.cpp
	.cfi_startproc
// %bb.0:
	stp	x29, x30, [sp, #-16]!           // 16-byte Folded Spill
	mov	x29, sp
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	bl	__cxx_global_var_init
	ldp	x29, x30, [sp], #16             // 16-byte Folded Reload
	ret
.Lfunc_end6:
	.size	_GLOBAL__sub_I_index.cpp, .Lfunc_end6-_GLOBAL__sub_I_index.cpp
	.cfi_endproc
                                        // -- End function
	.type	_ZStL8__ioinit,@object          // @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L__const.main.arr,@object      // @__const.main.arr
	.section	.rodata,"a",@progbits
	.p2align	2
.L__const.main.arr:
	.word	9                               // 0x9
	.word	3                               // 0x3
	.word	4                               // 0x4
	.word	2                               // 0x2
	.word	1                               // 0x1
	.word	8                               // 0x8
	.size	.L__const.main.arr, 24

	.type	.L.str,@object                  // @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	" "
	.size	.L.str, 2

	.section	.init_array,"aw",@init_array
	.p2align	3
	.xword	_GLOBAL__sub_I_index.cpp
	.ident	"Ubuntu clang version 14.0.0-1ubuntu1"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __cxx_global_var_init
	.addrsig_sym __cxa_atexit
	.addrsig_sym _Z9partitionPiii
	.addrsig_sym _ZSt4swapIiENSt9enable_ifIXsr6__and_ISt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS3_ESt18is_move_assignableIS3_EEE5valueEvE4typeERS3_SC_
	.addrsig_sym _Z9quickSortPiii
	.addrsig_sym _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	.addrsig_sym _ZNSolsEi
	.addrsig_sym _ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.addrsig_sym _GLOBAL__sub_I_index.cpp
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
	.addrsig_sym _ZSt4cout
