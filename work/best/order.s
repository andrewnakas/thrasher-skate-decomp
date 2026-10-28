
.file	1 "stdin"
gcc2_compiled.:
__gnu_compiled_c:
.text
.align	2
.globl	fa
.text
.ent	fa
.set	noreorder
fa:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$5
mflo	$4
srl	$3,$4,16
sll	$2,$5,16
j	$31
or	$2,$3,$2

.end	fa
.align	2
.globl	fb
.text
.ent	fb
.set	noreorder
fb:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$5
mflo	$4
srl	$3,$4,16
sll	$2,$5,16
j	$31
or	$2,$3,$2

.end	fb
.align	2
.globl	fc
.text
.ent	fc
.set	noreorder
fc:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$7
mflo	$6
srl	$2,$6,16
sll	$4,$7,16
or	$2,$2,$4
j	$31
sra	$3,$7,16

.end	fc
.align	2
.globl	fd
.text
.ent	fd
.set	noreorder
fd:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$7
mflo	$6
srl	$2,$6,16
sll	$4,$7,16
or	$2,$2,$4
j	$31
sra	$3,$7,16

.end	fd
.align	2
.globl	fe
.text
.ent	fe
.set	noreorder
fe:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$5
mflo	$4
sra	$3,$4,16
sll	$2,$5,16
j	$31
or	$2,$3,$2

.end	fe
.align	2
.globl	ff
.text
.ent	ff
.set	noreorder
ff:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$5
mflo	$4
srl	$3,$4,16
sll	$2,$5,16
j	$31
or	$2,$3,$2

.end	ff
.align	2
.globl	fg
.text
.ent	fg
.set	noreorder
fg:
.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
mfhi	$5
mflo	$4
srl	$2,$4,16
sll	$3,$5,16
j	$31
or	$2,$2,$3

.end	fg
.align	2
.globl	fh
.text
.ent	fh
.set	noreorder
fh:
.frame	$sp,8,$31		# vars= 8, regs= 0/0, args= 0, extra= 0
.mask	0x00000000,0
.fmask	0x00000000,0
mult	$4,$5
subu	$sp,$sp,8
mfhi	$7
mflo	$6
sw	$6,0($sp)
sw	$7,4($sp)
lw	$2,4($sp)
#nop # DEBUG: 'lhu	$3,2($sp)' does not load from $2
lhu	$3,2($sp)
#nop # DEBUG: 'sll	$2,$2,16' does not load from $3
sll	$2,$2,16
or	$2,$3,$2
j	$31
addu	$sp,$sp,8

.end	fh
