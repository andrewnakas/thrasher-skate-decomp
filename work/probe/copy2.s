
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	q1
.text
.ent	q1
.set	noreorder
q1:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	q1
.align	2
.globl	q2
.text
.ent	q2
.set	noreorder
q2:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lui	$2,%hi(D_8008B384) # high
addiu	$2,$2,%lo(D_8008B384) # low
sll	$5,$5,2
addu	$5,$5,$2
lw	$3,0($5)
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,0($5)
j	$31
sw	$4,0($3)

.end	q2
.align	2
.globl	q3
.text
.ent	q3
.set	noreorder
q3:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
sll	$5,$5,2
lui	$2,%hi(D_8008B384) # high
addiu	$2,$2,%lo(D_8008B384) # low
addu	$5,$5,$2
lw	$3,0($5)
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,0($5)
j	$31
sw	$4,0($3)

.end	q3
.align	2
.globl	q4
.text
.ent	q4
.set	noreorder
q4:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lui	$2,%hi(D_8008B388) # high
addiu	$2,$2,%lo(D_8008B388) # low
sll	$5,$5,2
addu	$5,$5,$2
lw	$3,0($5)
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,0($5)
j	$31
sw	$4,0($3)

.end	q4
.align	2
.globl	q5
.text
.ent	q5
.set	noreorder
q5:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lui	$2,%hi(D_8008B388) # high
addiu	$2,$2,%lo(D_8008B388) # low
sll	$5,$5,2
addu	$5,$5,$2
lw	$3,0($5)
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,0($5)
j	$31
sw	$4,0($3)

.end	q5
.align	2
.globl	q6
.text
.ent	q6
.set	noreorder
q6:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
sll	$5,$5,2
lui	$2,%hi(D_8008B388) # high
addiu	$2,$2,%lo(D_8008B388) # low
addu	$5,$5,$2
lw	$3,0($5)
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,0($5)
j	$31
sw	$4,0($3)

.end	q6
.align	2
.globl	q7
.text
.ent	q7
.set	noreorder
q7:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,20' does not use $at
addu	$2,$3,20
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	q7

.extern	D_8008B060, 4
