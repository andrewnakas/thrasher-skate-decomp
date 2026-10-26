
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	func_8003ED04
.text
.ent	func_8003ED04
.set	noreorder
func_8003ED04:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,D_8008B328
sw	$2,D_8008B330
addu	$2,$2,9168
sw	$2,D_8008B32C
j	$31
nop  # DEBUG: branch/jump
.end	func_8003ED04

.extern	D_8008B32C, 4
.extern	D_8008B328, 4
.extern	D_8008B330, 4
