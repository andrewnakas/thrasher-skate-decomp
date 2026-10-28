
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	e1
.text
.ent	e1
.set	noreorder
e1:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
addu	$6,$5,$zero
lw	$2,0($4)
#nop # DEBUG: 'sra	$7,$5,31' does not load from $2
sra	$7,$5,31
addu	$8,$2,$zero
sra	$9,$2,31
multu	$8,$6
mfhi	$3
mflo	$2
nop
nop
mult	$8,$7
# #nop  # DEBUG: skipped
# #nop  # DEBUG: skipped
# mult	$8,$7  # DEBUG: skipped
mflo	$11
nop
nop
mult	$6,$9
# #nop  # DEBUG: skipped
# #nop  # DEBUG: skipped
# mult	$6,$9  # DEBUG: skipped
addu	$3,$3,$11
mflo	$5
addu	$3,$3,$5
srl	$2,$2,16
sll	$5,$3,16
or	$2,$2,$5
sra	$3,$3,16
j	$31
sw	$2,0($4)

.end	e1
.align	2
.globl	e2
.text
.ent	e2
.set	noreorder
e2:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$7
mflo	$6
srl	$2,$6,16
sll	$5,$7,16
or	$2,$2,$5
sra	$3,$7,16
j	$31
sw	$2,0($4)

.end	e2
.align	2
.globl	e3
.text
.ent	e3
.set	noreorder
e3:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$7
mflo	$6
srl	$2,$6,16
sll	$5,$7,16
or	$2,$2,$5
srl	$3,$7,16
j	$31
sw	$2,0($4)

.end	e3
.align	2
.globl	e4
.text
.ent	e4
.set	noreorder
e4:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$3
mflo	$2
sll	$5,$3,16
sra	$2,$2,16
or	$5,$5,$2
j	$31
sw	$5,0($4)

.end	e4
.align	2
.globl	e5
.text
.ent	e5
.set	noreorder
e5:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$7
mflo	$6
srl	$2,$6,16
sll	$5,$7,16
or	$2,$2,$5
sra	$3,$7,16
j	$31
sw	$2,0($4)

.end	e5
.align	2
.globl	e6
.text
.ent	e6
.set	noreorder
e6:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'mult	$2,$5' does not use $at
mult	$2,$5
mfhi	$3
mflo	$2
sll	$5,$3,16
sra	$2,$2,16
or	$5,$5,$2
j	$31
sw	$5,0($4)

.end	e6
