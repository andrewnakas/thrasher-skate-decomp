
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	p1
.text
.ent	p1
.set	noreorder
p1:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,16' does not use $at
addu	$2,$3,16
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	p1
.align	2
.globl	p2
.text
.ent	p2
.set	noreorder
p2:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,16' does not use $at
addu	$2,$3,16
sw	$2,D_8008B060
j	$31
sb	$4,0($3)

.end	p2
.align	2
.globl	p3
.text
.ent	p3
.set	noreorder
p3:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,16' does not use $at
addu	$2,$3,16
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	p3
.align	2
.globl	p4
.text
.ent	p4
.set	noreorder
p4:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,16' does not use $at
addu	$2,$3,16
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	p4
.align	2
.globl	p5
.text
.ent	p5
.set	noreorder
p5:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$2,D_8008B060
#nop # DEBUG: 'sll	$5,$5,2' does not load from $2
sll	$5,$5,2
addu	$2,$2,$5
lw	$5,0($2)
nop # DEBUG: Reuse of '$5'. 'addu	$3,$5,16' does not use $at
addu	$3,$5,16
sw	$3,0($2)
j	$31
sw	$4,0($5)

.end	p5
.align	2
.globl	p6
.text
.ent	p6
.set	noreorder
p6:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,16' does not use $at
addu	$2,$3,16
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	p6
.align	2
.globl	p7
.text
.ent	p7
.set	noreorder
p7:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
lw	$3,D_8008B060
nop # DEBUG: Reuse of '$3'. 'addu	$2,$3,16' does not use $at
addu	$2,$3,16
sw	$2,D_8008B060
j	$31
sw	$4,0($3)

.end	p7

.extern	D_8008B060, 4
