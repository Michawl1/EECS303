	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"pwmC.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"/sys/class/gpio/export\000"
	.align	2
.LC1:
	.ascii	"Failed to open export for writing!\012\000"
	.align	2
.LC2:
	.ascii	"%d\000"
	.text
	.align	2
	.type	GPIOExport, %function
GPIOExport:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	ldr	r0, .L5
	mov	r1, #1
	bl	open
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmn	r3, #1
	bne	.L2
	ldr	r3, .L5+4
	ldr	r3, [r3]
	ldr	r0, .L5+8
	mov	r1, #1
	mov	r2, #35
	bl	fwrite
	mvn	r3, #0
	b	.L4
.L2:
	sub	r3, fp, #16
	mov	r0, r3
	mov	r1, #3
	ldr	r2, .L5+12
	ldr	r3, [fp, #-24]
	bl	snprintf
	str	r0, [fp, #-12]
	ldr	r3, [fp, #-12]
	sub	r2, fp, #16
	ldr	r0, [fp, #-8]
	mov	r1, r2
	mov	r2, r3
	bl	write
	ldr	r0, [fp, #-8]
	bl	close
	mov	r3, #0
.L4:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L6:
	.align	2
.L5:
	.word	.LC0
	.word	stderr
	.word	.LC1
	.word	.LC2
	.size	GPIOExport, .-GPIOExport
	.section	.rodata
	.align	2
.LC3:
	.ascii	"/sys/class/gpio/unexport\000"
	.align	2
.LC4:
	.ascii	"Failed to open unexport for writing!\012\000"
	.text
	.align	2
	.type	GPIOUnexport, %function
GPIOUnexport:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	ldr	r0, .L11
	mov	r1, #1
	bl	open
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmn	r3, #1
	bne	.L8
	ldr	r3, .L11+4
	ldr	r3, [r3]
	ldr	r0, .L11+8
	mov	r1, #1
	mov	r2, #37
	bl	fwrite
	mvn	r3, #0
	b	.L10
.L8:
	sub	r3, fp, #16
	mov	r0, r3
	mov	r1, #3
	ldr	r2, .L11+12
	ldr	r3, [fp, #-24]
	bl	snprintf
	str	r0, [fp, #-12]
	ldr	r3, [fp, #-12]
	sub	r2, fp, #16
	ldr	r0, [fp, #-8]
	mov	r1, r2
	mov	r2, r3
	bl	write
	ldr	r0, [fp, #-8]
	bl	close
	mov	r3, #0
.L10:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L12:
	.align	2
.L11:
	.word	.LC3
	.word	stderr
	.word	.LC4
	.word	.LC2
	.size	GPIOUnexport, .-GPIOUnexport
	.section	.rodata
	.align	2
.LC5:
	.ascii	"/sys/class/gpio/gpio%d/direction\000"
	.align	2
.LC6:
	.ascii	"Failed to open gpio direction for writing!\012\000"
	.align	2
.LC7:
	.ascii	"Failed to set direction!\012\000"
	.text
	.align	2
	.type	GPIODirection, %function
GPIODirection:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #48
	str	r0, [fp, #-48]
	str	r1, [fp, #-52]
	sub	r3, fp, #44
	mov	r0, r3
	mov	r1, #35
	ldr	r2, .L22
	ldr	r3, [fp, #-48]
	bl	snprintf
	sub	r3, fp, #44
	mov	r0, r3
	mov	r1, #1
	bl	open
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmn	r3, #1
	bne	.L14
	ldr	r3, .L22+4
	ldr	r3, [r3]
	ldr	r0, .L22+8
	mov	r1, #1
	mov	r2, #43
	bl	fwrite
	mvn	r3, #0
	b	.L21
.L14:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	bne	.L16
	mov	r3, #0
	b	.L17
.L16:
	mov	r3, #3
.L17:
	ldr	r2, .L22+12
	add	r2, r3, r2
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	bne	.L18
	mov	r3, #2
	b	.L19
.L18:
	mov	r3, #3
.L19:
	ldr	r0, [fp, #-8]
	mov	r1, r2
	mov	r2, r3
	bl	write
	mov	r3, r0
	cmn	r3, #1
	bne	.L20
	ldr	r3, .L22+4
	ldr	r3, [r3]
	ldr	r0, .L22+16
	mov	r1, #1
	mov	r2, #25
	bl	fwrite
	mvn	r3, #0
	b	.L21
.L20:
	ldr	r0, [fp, #-8]
	bl	close
	mov	r3, #0
.L21:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L23:
	.align	2
.L22:
	.word	.LC5
	.word	stderr
	.word	.LC6
	.word	s_directions_str.5846
	.word	.LC7
	.size	GPIODirection, .-GPIODirection
	.section	.rodata
	.align	2
.LC8:
	.ascii	"/sys/class/gpio/gpio%d/value\000"
	.align	2
.LC9:
	.ascii	"Failed to open gpio value for reading!\012\000"
	.align	2
.LC10:
	.ascii	"Failed to read value!\012\000"
	.text
	.align	2
	.type	GPIORead, %function
GPIORead:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #48
	str	r0, [fp, #-48]
	sub	r3, fp, #40
	mov	r0, r3
	mov	r1, #30
	ldr	r2, .L29
	ldr	r3, [fp, #-48]
	bl	snprintf
	sub	r3, fp, #40
	mov	r0, r3
	mov	r1, #0
	bl	open
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmn	r3, #1
	bne	.L25
	ldr	r3, .L29+4
	ldr	r3, [r3]
	ldr	r0, .L29+8
	mov	r1, #1
	mov	r2, #39
	bl	fwrite
	mvn	r3, #0
	b	.L28
.L25:
	sub	r3, fp, #44
	ldr	r0, [fp, #-8]
	mov	r1, r3
	mov	r2, #3
	bl	read
	mov	r3, r0
	cmn	r3, #1
	bne	.L27
	ldr	r3, .L29+4
	ldr	r3, [r3]
	ldr	r0, .L29+12
	mov	r1, #1
	mov	r2, #22
	bl	fwrite
	mvn	r3, #0
	b	.L28
.L27:
	ldr	r0, [fp, #-8]
	bl	close
	sub	r3, fp, #44
	mov	r0, r3
	bl	atoi
	mov	r3, r0
.L28:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L30:
	.align	2
.L29:
	.word	.LC8
	.word	stderr
	.word	.LC9
	.word	.LC10
	.size	GPIORead, .-GPIORead
	.section	.rodata
	.align	2
.LC11:
	.ascii	"Failed to open gpio value for writing!\012\000"
	.align	2
.LC12:
	.ascii	"Failed to write value!\012\000"
	.text
	.align	2
	.type	GPIOWrite, %function
GPIOWrite:
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #48
	str	r0, [fp, #-48]
	str	r1, [fp, #-52]
	sub	r3, fp, #40
	mov	r0, r3
	mov	r1, #30
	ldr	r2, .L36
	ldr	r3, [fp, #-48]
	bl	snprintf
	sub	r3, fp, #40
	mov	r0, r3
	mov	r1, #1
	bl	open
	str	r0, [fp, #-8]
	ldr	r3, [fp, #-8]
	cmn	r3, #1
	bne	.L32
	ldr	r3, .L36+4
	ldr	r3, [r3]
	ldr	r0, .L36+8
	mov	r1, #1
	mov	r2, #39
	bl	fwrite
	mvn	r3, #0
	b	.L35
.L32:
	ldr	r3, [fp, #-52]
	cmp	r3, #0
	movne	r3, #1
	moveq	r3, #0
	uxtb	r3, r3
	mov	r2, r3
	ldr	r3, .L36+12
	add	r3, r2, r3
	ldr	r0, [fp, #-8]
	mov	r1, r3
	mov	r2, #1
	bl	write
	mov	r3, r0
	cmp	r3, #1
	beq	.L34
	ldr	r3, .L36+4
	ldr	r3, [r3]
	ldr	r0, .L36+16
	mov	r1, #1
	mov	r2, #23
	bl	fwrite
	mvn	r3, #0
	b	.L35
.L34:
	ldr	r0, [fp, #-8]
	bl	close
	mov	r3, #0
.L35:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L37:
	.align	2
.L36:
	.word	.LC8
	.word	stderr
	.word	.LC11
	.word	s_values_str.5859
	.word	.LC12
	.size	GPIOWrite, .-GPIOWrite
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	mov	r3, #1
	str	r3, [fp, #-8]
	mov	r0, #20
	bl	GPIOExport
	mov	r3, r0
	cmn	r3, #1
	beq	.L39
	mov	r0, #24
	bl	GPIOExport
	mov	r3, r0
	cmn	r3, #1
	bne	.L40
.L39:
	mov	r3, #1
	b	.L41
.L40:
	mov	r0, #20
	mov	r1, #1
	bl	GPIODirection
	mov	r3, r0
	cmn	r3, #1
	beq	.L42
	mov	r0, #24
	mov	r1, #0
	bl	GPIODirection
	mov	r3, r0
	cmn	r3, #1
	bne	.L43
.L42:
	mov	r3, #2
	b	.L41
.L43:
	ldr	r2, [fp, #-8]
	mov	r3, r2, asr #31
	mov	r3, r3, lsr #31
	add	r2, r2, r3
	and	r2, r2, #1
	rsb	r3, r3, r2
	mov	r0, #20
	mov	r1, r3
	bl	GPIOWrite
	mov	r3, r0
	cmn	r3, #1
	bne	.L44
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	mov	r3, #3
	b	.L41
.L44:
	ldr	r3, [fp, #-8]
	sub	r3, r3, #1
	str	r3, [fp, #-8]
	ldr	r0, .L45
	bl	usleep
	b	.L43
.L41:
	mov	r0, r3
	sub	sp, fp, #4
	@ sp needed
	ldmfd	sp!, {fp, pc}
.L46:
	.align	2
.L45:
	.word	750
	.size	main, .-main
	.section	.rodata
	.align	2
	.type	s_directions_str.5846, %object
	.size	s_directions_str.5846, 7
s_directions_str.5846:
	.ascii	"in\000out\000"
	.align	2
	.type	s_values_str.5859, %object
	.size	s_values_str.5859, 3
s_values_str.5859:
	.ascii	"01\000"
	.ident	"GCC: (Raspbian 4.9.2-10) 4.9.2"
	.section	.note.GNU-stack,"",%progbits
