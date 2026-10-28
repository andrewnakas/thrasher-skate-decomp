
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	e7
.text
.ent	e7
.set	noreorder
e7:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$3
mflo	$2
srl	$5,$2,16
sll	$2,$3,16
or	$5,$5,$2
j	$31
sw	$5,0($4)

.end	e7
.align	2
.globl	e8
.text
.ent	e8
.set	noreorder
e8:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$3
mflo	$2
srl	$5,$2,16
sll	$2,$3,16
or	$5,$5,$2
j	$31
sw	$5,0($4)

.end	e8
