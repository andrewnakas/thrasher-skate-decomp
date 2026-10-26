
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.text
.ent	mask8
.set	noreorder
mask8:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
j	$31
andi	$2,$4,0x00ff

.end	mask8
.align	2
.globl	m17
.text
.ent	m17
.set	noreorder
m17:
.frame	$sp,24,$31		# vars= 0, regs= 2/0, args= 16, extra= 0
.mask	0x80010000,-4
.fmask	0x00000000,0
subu	$sp,$sp,24
sw	$16,16($sp)
addu	$16,$4,$zero
sw	$31,20($sp)
lbu	$4,2($16)
#nop # DEBUG: 'jal	mask8' does not load from $4
jal	mask8
nop  # DEBUG: branch/jump
lbu	$4,3($16)
#nop # DEBUG: 'jal	mask8' does not load from $4
jal	mask8
addu	$16,$2,$zero

sll	$16,$16,8
nor	$2,$2,$16
lw	$31,20($sp)
#nop # DEBUG: 'lw	$16,16($sp)' does not load from $31
lw	$16,16($sp)
#nop # DEBUG: 'andi	$2,$2,0xffff' does not load from $16
andi	$2,$2,0xffff
j	$31
addu	$sp,$sp,24

.end	m17
.align	2
.globl	k01
.text
.ent	k01
.set	noreorder
k01:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
li	$2,4096			# 0x00001000
beq	$6,$2,$L5
addu	$8,$4,$zero

sll	$3,$7,2
lui	$2,%hi(D_8008B384) # high
addiu	$2,$2,%lo(D_8008B384) # low
addu	$3,$3,$2
lw	$4,0($3)
nop # DEBUG: Reuse of '$4'. 'addu	$2,$4,20' does not use $at
addu	$2,$4,20
sw	$2,0($3)
sw	$8,0($4)
lw	$2,0($5)
nop # DEBUG: Reuse of '$2'. 'sw	$2,4($4)' does not use $at
sw	$2,4($4)
lw	$2,4($5)
nop # DEBUG: Reuse of '$2'. 'sw	$2,8($4)' does not use $at
sw	$2,8($4)
lw	$2,8($5)
#nop # DEBUG: 'sw	$6,16($4)' does not load from $2
sw	$6,16($4)
sw	$2,12($4)
$L5:
j	$31
nop  # DEBUG: branch/jump
.end	k01
.align	2
.globl	k02
.text
.ent	k02
.set	noreorder
k02:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
li	$2,4096			# 0x00001000
beq	$6,$2,$L8
addu	$5,$4,$zero

lui	$4,%hi(D_8008B384) # high
addiu	$3,$4,%lo(D_8008B384) # low
sll	$2,$7,2
addu	$2,$2,$3
lw	$3,0($2)
nop # DEBUG: Reuse of '$3'. 'sw	$3,%lo(D_8008B384)($4)' does not use $at
sw	$3,%lo(D_8008B384)($4)
addu	$4,$3,20
sw	$4,0($2)
sw	$5,0($3)
$L8:
j	$31
nop  # DEBUG: branch/jump
.end	k02
.align	2
.globl	k03
.text
.ent	k03
.set	noreorder
k03:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
li	$2,4096			# 0x00001000
beq	$6,$2,$L11
addu	$8,$4,$zero

sll	$3,$7,2
lui	$2,%hi(D_8008B384) # high
addiu	$2,$2,%lo(D_8008B384) # low
addu	$3,$3,$2
lw	$4,0($3)
nop # DEBUG: Reuse of '$4'. 'addu	$2,$4,20' does not use $at
addu	$2,$4,20
sw	$2,0($3)
sw	$8,0($4)
lw	$2,0($5)
nop # DEBUG: Reuse of '$2'. 'sw	$2,4($4)' does not use $at
sw	$2,4($4)
lw	$2,4($5)
nop # DEBUG: Reuse of '$2'. 'sw	$2,8($4)' does not use $at
sw	$2,8($4)
lw	$2,8($5)
#nop # DEBUG: 'sw	$6,16($4)' does not load from $2
sw	$6,16($4)
sw	$2,12($4)
$L11:
j	$31
nop  # DEBUG: branch/jump
.end	k03
.align	2
.globl	k04
.text
.ent	k04
.set	noreorder
k04:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
li	$2,4096			# 0x00001000
beq	$6,$2,$L14
addu	$5,$4,$zero

lui	$2,%hi(D_8008B384) # high
addiu	$2,$2,%lo(D_8008B384) # low
sll	$3,$7,2
addu	$3,$3,$2
lw	$4,0($3)
nop # DEBUG: Reuse of '$4'. 'lw	$2,0($4)' does not use $at
lw	$2,0($4)
nop # DEBUG: Reuse of '$2'. 'addu	$2,$2,20' does not use $at
addu	$2,$2,20
sw	$2,0($3)
sw	$5,0($4)
$L14:
j	$31
nop  # DEBUG: branch/jump
.end	k04
.align	2
.globl	k05
.text
.ent	k05
.set	noreorder
k05:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
li	$2,4096			# 0x00001000
beq	$6,$2,$L17
addu	$8,$4,$zero

lui	$2,%hi(D_8008B384) # high
addiu	$2,$2,%lo(D_8008B384) # low
sll	$3,$7,2
addu	$3,$3,$2
lw	$4,0($3)
nop # DEBUG: Reuse of '$4'. 'addu	$2,$4,20' does not use $at
addu	$2,$4,20
sw	$2,0($3)
sw	$8,0($4)
lw	$2,0($5)
nop # DEBUG: Reuse of '$2'. 'sw	$2,4($4)' does not use $at
sw	$2,4($4)
$L17:
j	$31
nop  # DEBUG: branch/jump
.end	k05
