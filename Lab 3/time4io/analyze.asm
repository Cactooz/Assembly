  # analyze.asm
  # This file written 2015 by F Lundevall
  # Copyright abandoned - this file is in the public domain.

	.text
main:
	li $s0,0x30
loop:
	move $a0,$s0		# copy from s0 to a0
	
	li $v0,11			# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window

	addi	$s0,$s0,3		#3, makes the code jump 3 steps
	
	li $t0,0x5D		#stop when we reach 3 places after Z
	bne $s0,$t0,loop
	nop				# delay slot filler (just in case)

stop:	j stop			# loop forever here
	nop				# delay slot filler (just in case)
