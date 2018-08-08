	.import	printi
	.import	printc
	.import	readi
	.import	readc
	.import	exit
	.import	time
	.import	clearAll
	.import	setPixel
	.import	drawLine
	.import	drawCircle
	.import	_indexError

	.code
	.align	4

	.export	main
main:
	sub	$29,$29,12		; allocate frame
	stw	$25,$29,4		; save old frame pointer
	add	$25,$29,12		; setup new frame pointer
	stw	$31,$25,-12		; save return register
	add	$8,$25,-4
	add	$9,$0,3
	add	$10,$0,2
	add	$9,$9,$10
	stw	$9,$8,0
	jal	andere
	ldw	$31,$25,-12		; restore return register
	ldw	$25,$29,4		; restore old frame pointer
	add	$29,$29,12		; release frame
	jr	$31			; return

	.export	andere
andere:
	sub	$29,$29,12		; allocate frame
	stw	$25,$29,0		; save old frame pointer
	add	$25,$29,12		; setup new frame pointer
	add	$8,$25,-4
	add	$9,$0,3
	add	$10,$0,5
	add	$9,$9,$10
	stw	$9,$8,0
	add	$8,$25,-8
	add	$9,$0,0
	stw	$9,$8,0
L0:
	add	$8,$25,-8
	ldw	$8,$8,0
	add	$9,$25,-4
	ldw	$9,$9,0
	bge	$8,$9,L1
	add	$8,$25,-8
	add	$9,$25,-8
	ldw	$9,$9,0
	add	$10,$0,1
	add	$9,$9,$10
	stw	$9,$8,0
	j	L0
L1:
	ldw	$25,$29,0		; restore old frame pointer
	add	$29,$29,12		; release frame
	jr	$31			; return
