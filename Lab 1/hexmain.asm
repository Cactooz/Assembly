  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li $a0,17			# change this to test different values

	jal hexasc		# call hexasc
	nop				# delay slot filler (just in case)	

	move $a0,$v0		# copy return value to argument register

	li $v0,11			# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j stop			# stop after one run
	nop				# delay slot filler (just in case)

  # You can write your own code for hexasc here
hexasc:
	and $t0, $a0, 0x0F #Mask out all bits except the first LSBx16 and save to $t0
	slti $t1, $t0, 10 #Check if $t0 < 10
	beq $t1, 1, numbers #Branch to numbers if $t1=1
	nop #Delay
	
	addi $t0, $a0, 0x37 #Add 0x37 to get to the correct ASCII letter values
	move $v0, $t0 #Move the output into the return
	
	jr $ra #Return $ra
	
numbers:
	addi $t0, $t0, 0x30 #Add 0x30 to get the correct ASCII number values
	move $v0, $t0 #Move the output into the return
	
	jr $ra #Return $ra