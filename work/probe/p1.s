
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	f1
.text
.ent	f1
.set	noreorder
f1:
.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
.mask	0x80030000,-8
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,32' does not load from $2
subu	$sp,$sp,32
sw	$17,20($sp)
addu	$17,$0,$zero
sw	$31,24($sp)
beq	$3,$2,$L2
sw	$16,16($sp)

addu	$17,$17,1
$L7:
lw	$4,B
#nop # DEBUG: 'sll	$16,$17,4' does not load from $4
sll	$16,$17,4
jal	g
subu	$4,$4,$16

lw	$2,B
#nop # DEBUG: 'lw	$3,A' does not load from $2
lw	$3,A
#nop # DEBUG: 'subu	$2,$2,$16' does not load from $3
subu	$2,$2,$16
sltu	$3,$3,$2
bne	$3,$0,$L7
addu	$17,$17,1

$L2:
lw	$31,24($sp)
#nop # DEBUG: 'lw	$17,20($sp)' does not load from $31
lw	$17,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $17
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,32

.end	f1
.align	2
.globl	f2
.text
.ent	f2
.set	noreorder
f2:
.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
.mask	0x80030000,-8
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,32' does not load from $2
subu	$sp,$sp,32
sw	$31,24($sp)
sw	$17,20($sp)
beq	$3,$2,$L9
sw	$16,16($sp)

li	$17,1			# 0x00000001
$L10:
lw	$16,B
#nop # DEBUG: 'sll	$2,$17,4' does not load from $16
sll	$2,$17,4
subu	$16,$16,$2
jal	g
addu	$4,$16,$zero

lw	$2,A
nop # DEBUG: Reuse of '$2'. 'sltu	$2,$2,$16' does not use $at
sltu	$2,$2,$16
bne	$2,$0,$L10
addu	$17,$17,1

$L9:
lw	$31,24($sp)
#nop # DEBUG: 'lw	$17,20($sp)' does not load from $31
lw	$17,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $17
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,32

.end	f2
.align	2
.globl	f3
.text
.ent	f3
.set	noreorder
f3:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
lw	$5,B
#nop # DEBUG: 'lw	$3,A' does not load from $5
lw	$3,A
#nop # DEBUG: 'subu	$sp,$sp,24' does not load from $3
subu	$sp,$sp,24
sw	$16,16($sp)
addu	$16,$0,$zero
beq	$3,$5,$L15
sw	$31,20($sp)

addu	$2,$5,-16
sltu	$2,$3,$2
beq	$2,$0,$L15
addu	$16,$16,1

$L21:
sll	$4,$16,4
jal	g
subu	$4,$5,$4

addu	$2,$16,1
sll	$2,$2,4
lw	$5,B
#nop # DEBUG: 'lw	$3,A' does not load from $5
lw	$3,A
#nop # DEBUG: 'subu	$2,$5,$2' does not load from $3
subu	$2,$5,$2
sltu	$3,$3,$2
bne	$3,$0,$L21
addu	$16,$16,1

$L15:
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,24

.end	f3
.align	2
.globl	f4
.text
.ent	f4
.set	noreorder
f4:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
lw	$4,B
#nop # DEBUG: 'lw	$3,A' does not load from $4
lw	$3,A
#nop # DEBUG: 'subu	$sp,$sp,24' does not load from $3
subu	$sp,$sp,24
sw	$31,20($sp)
beq	$3,$4,$L23
sw	$16,16($sp)

addu	$2,$4,-16
sltu	$2,$3,$2
beq	$2,$0,$L23
li	$16,16			# 0x00000010

$L26:
jal	g
subu	$4,$4,$16

addu	$16,$16,16
lw	$4,B
#nop # DEBUG: 'lw	$2,A' does not load from $4
lw	$2,A
#nop # DEBUG: 'subu	$3,$4,$16' does not load from $2
subu	$3,$4,$16
sltu	$2,$2,$3
bne	$2,$0,$L26
nop  # DEBUG: branch/jump
$L23:
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,24

.end	f4
.align	2
.globl	f5
.text
.ent	f5
.set	noreorder
f5:
.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
.mask	0x80030000,-8
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,32' does not load from $2
subu	$sp,$sp,32
sw	$17,20($sp)
addu	$17,$0,$zero
sw	$31,24($sp)
beq	$3,$2,$L29
sw	$16,16($sp)

addu	$17,$17,1
$L34:
lw	$4,B
#nop # DEBUG: 'sll	$16,$17,4' does not load from $4
sll	$16,$17,4
jal	g
subu	$4,$4,$16

lw	$2,B
#nop # DEBUG: 'lw	$3,A' does not load from $2
lw	$3,A
#nop # DEBUG: 'subu	$2,$2,$16' does not load from $3
subu	$2,$2,$16
sltu	$3,$3,$2
bne	$3,$0,$L34
addu	$17,$17,1

$L29:
lw	$31,24($sp)
#nop # DEBUG: 'lw	$17,20($sp)' does not load from $31
lw	$17,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $17
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,32

.end	f5
.align	2
.globl	f6
.text
.ent	f6
.set	noreorder
f6:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
lw	$2,A
#nop # DEBUG: 'lw	$3,B' does not load from $2
lw	$3,B
#nop # DEBUG: 'subu	$sp,$sp,24' does not load from $3
subu	$sp,$sp,24
sw	$31,20($sp)
beq	$2,$3,$L36
sw	$16,16($sp)

addu	$4,$3,-16
sltu	$2,$2,$4
beq	$2,$0,$L36
li	$16,1			# 0x00000001

$L40:
jal	g
addu	$16,$16,1

sll	$4,$16,4
lw	$3,B
#nop # DEBUG: 'lw	$2,A' does not load from $3
lw	$2,A
#nop # DEBUG: 'subu	$4,$3,$4' does not load from $2
subu	$4,$3,$4
sltu	$2,$2,$4
bne	$2,$0,$L40
nop  # DEBUG: branch/jump
$L36:
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,24

.end	f6
.align	2
.globl	f7
.text
.ent	f7
.set	noreorder
f7:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
lw	$4,B
#nop # DEBUG: 'lw	$3,A' does not load from $4
lw	$3,A
#nop # DEBUG: 'subu	$sp,$sp,24' does not load from $3
subu	$sp,$sp,24
sw	$31,20($sp)
beq	$3,$4,$L43
sw	$16,16($sp)

addu	$2,$4,-16
sltu	$2,$3,$2
beq	$2,$0,$L43
li	$16,16			# 0x00000010

$L47:
jal	g
subu	$4,$4,$16

addu	$16,$16,16
lw	$4,B
#nop # DEBUG: 'lw	$2,A' does not load from $4
lw	$2,A
#nop # DEBUG: 'subu	$3,$4,$16' does not load from $2
subu	$3,$4,$16
sltu	$2,$2,$3
bne	$2,$0,$L47
nop  # DEBUG: branch/jump
$L43:
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,24

.end	f7
.align	2
.globl	f8
.text
.ent	f8
.set	noreorder
f8:
.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
.mask	0x80030000,-8
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,32' does not load from $2
subu	$sp,$sp,32
sw	$17,20($sp)
addu	$17,$0,$zero
sw	$31,24($sp)
beq	$3,$2,$L50
sw	$16,16($sp)

addu	$17,$17,1
lw	$4,B
#nop # DEBUG: 'sll	$16,$17,4' does not load from $4
$L57:
sll	$16,$17,4
jal	g
subu	$4,$4,$16

lw	$4,B
#nop # DEBUG: 'lw	$2,A' does not load from $4
lw	$2,A
#nop # DEBUG: 'subu	$16,$4,$16' does not load from $2
subu	$16,$4,$16
sltu	$2,$2,$16
bne	$2,$0,$L57
addu	$17,$17,1

addu	$17,$17,-1
bgez	$17,$L50
nop  # DEBUG: branch/jump
jal	g
nop  # DEBUG: branch/jump
$L50:
lw	$31,24($sp)
#nop # DEBUG: 'lw	$17,20($sp)' does not load from $31
lw	$17,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $17
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,32

.end	f8
.align	2
.globl	f9
.text
.ent	f9
.set	noreorder
f9:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
lw	$2,A
#nop # DEBUG: 'lw	$4,B' does not load from $2
lw	$4,B
#nop # DEBUG: 'subu	$sp,$sp,24' does not load from $4
subu	$sp,$sp,24
sw	$31,20($sp)
beq	$2,$4,$L59
sw	$16,16($sp)

addu	$16,$4,$zero
addu	$16,$16,-16
$L64:
jal	g
addu	$4,$16,$zero

lw	$2,A
nop # DEBUG: Reuse of '$2'. 'sltu	$2,$2,$16' does not use $at
sltu	$2,$2,$16
bne	$2,$0,$L64
addu	$16,$16,-16

$L59:
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,24

.end	f9
.align	2
.globl	f10
.text
.ent	f10
.set	noreorder
f10:
.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
.mask	0x80030000,-8
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,32' does not load from $2
subu	$sp,$sp,32
sw	$17,20($sp)
addu	$17,$0,$zero
sw	$31,24($sp)
beq	$3,$2,$L66
sw	$16,16($sp)

addu	$17,$17,1
$L71:
lw	$4,B
#nop # DEBUG: 'sll	$16,$17,4' does not load from $4
sll	$16,$17,4
jal	g
subu	$4,$4,$16

lw	$2,B
#nop # DEBUG: 'lw	$3,A' does not load from $2
lw	$3,A
nop # DEBUG: Reuse of '$3'. 'subu	$2,$2,$3' does not use $at
subu	$2,$2,$3
sltu	$16,$16,$2
bne	$16,$0,$L71
addu	$17,$17,1

$L66:
lw	$31,24($sp)
#nop # DEBUG: 'lw	$17,20($sp)' does not load from $31
lw	$17,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $17
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,32

.end	f10
.align	2
.globl	f11
.text
.ent	f11
.set	noreorder
f11:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,24' does not load from $2
subu	$sp,$sp,24
sw	$16,16($sp)
addu	$16,$0,$zero
beq	$3,$2,$L73
sw	$31,20($sp)

addu	$16,$16,1
sll	$4,$16,4
$L80:
lw	$3,B
#nop # DEBUG: 'lw	$2,A' does not load from $3
lw	$2,A
#nop # DEBUG: 'subu	$4,$3,$4' does not load from $2
subu	$4,$3,$4
sltu	$2,$2,$4
beq	$2,$0,$L73
nop  # DEBUG: branch/jump
jal	g
addu	$16,$16,1

j	$L80
sll	$4,$16,4

$L73:
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,24

.end	f11
.align	2
.globl	f12
.text
.ent	f12
.set	noreorder
f12:
.frame	$sp,32,$31		# vars= 0, regs= 3/0, args= 16, extra= 0
.mask	0x80030000,-8
.fmask	0x00000000,0
lw	$3,A
#nop # DEBUG: 'lw	$2,B' does not load from $3
lw	$2,B
#nop # DEBUG: 'subu	$sp,$sp,32' does not load from $2
subu	$sp,$sp,32
sw	$17,20($sp)
addu	$17,$0,$zero
sw	$31,24($sp)
beq	$3,$2,$L82
sw	$16,16($sp)

addu	$17,$17,1
$L87:
lw	$4,B
#nop # DEBUG: 'sll	$16,$17,4' does not load from $4
sll	$16,$17,4
jal	g
subu	$4,$4,$16

lw	$3,B
#nop # DEBUG: 'lw	$2,A' does not load from $3
lw	$2,A
#nop # DEBUG: 'subu	$16,$3,$16' does not load from $2
subu	$16,$3,$16
sltu	$2,$2,$16
bne	$2,$0,$L87
addu	$17,$17,1

sw	$3,A
$L82:
lw	$31,24($sp)
#nop # DEBUG: 'lw	$17,20($sp)' does not load from $31
lw	$17,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $17
lw	$16,16($sp)
#nop # DEBUG: 'j	$31' does not load from $16
j	$31
addu	$sp,$sp,32

.end	f12

.extern	B, 4
.extern	A, 4
