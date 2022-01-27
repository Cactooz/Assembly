  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  # Please keep the two macros PUSH and POP unchanged

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
 
  # Please add your own code below this line
   
 hexasc:
	and $t0, $a0, 0x0F #Mask out all bits except the first LSBx16 and save to $t0
	slti $t1, $t0, 10 #Check if $t0 < 10
	beq $t1, 1, numbers #Branch to numbers if $t1=1
	nop #Delay
	
	addi $t0, $a0, 0x37 #Add 0x37 to get to the correct ASCII letter values
	move $v0, $t0 #Move the output into the return
	
	jr $ra #Return $ra
	nop
	
numbers:
	addi $t0, $t0, 0x30 #Add 0x30 to get the correct ASCII number values
	move $v0, $t0 #Move the output into the return
	
	jr $ra #Return $ra
	nop

delay:
	move $t0, $a0 #Save the input in ms from $a0 to $t0
	
	while:
		slt $t1, $0, $t0 #Check if 0 is smaller than $t0
		bne $t1, 1, end #If $t1 != 1 go to end
		nop
	
		add $t0, $t0, -1 #Remove one ms from $t0

		li $t2, 0 #Set $t2 to 0
		li $t3, 83 #Set t3 to 83
		
		for:
			slt $t4, $t2, $t3 #Check if $t2 is less than 400
			bne $t4, 1, forEnd #If $t3 != 1 go to end
			nop
		
			add $t2, $t2, 1 #Add 1 to $t1
			j for
			nop

		forEnd:
		j while #Go back to the start of the while loop
		nop

	end:
	jr $ra
	nop
	
time2string:
	PUSH($ra) #Push $ra to the stack
	PUSH($s0) #Push $s0 to the stack
	PUSH($s1) #Push $s1 to the stack
	
	move $s0, $a0 #Save $a0 to $s1
	move $s1, $a1 #Save $a1 to $s1
	
	#Mm:ss
	srl $t1, $s1, 12 #Shift 12 steps to the right
	move $a0, $t1 #Move $t1 to $a0
	
	jal hexasc #Go to hexasc
	nop
	
	sb $v0, 0($s0) #Copy $v0 to $s0
	
	#mM:ss
	srl $t1, $s1, 8 #Shift 8 steps to the right
	move $a0, $t1 #Move $t1 to $a0
	
	jal hexasc #Go to hexasc
	nop
	
	sb $v0, 1($s0) #Copy $v0 to $s0
	
	#mm : ss
	li $t0, 0x3A #Add : to $t0
	sb $t0, 2($s0) #Copy $t0 to $s0
	
	#mm:Ss
	srl $t1, $s1, 4 #Shift 4 steps to the right
	move $a0, $t1 #Move $t1 to $a0
	
	jal hexasc #Go to hexasc
	nop
	
	sb $v0, 3($s0) #Copy $v0 to $s0
	
	#mm:sS
	move $a0, $s1 #Move $s1 to $a0
	
	jal hexasc #Go to hexasc
	nop
	
	sb $v0, 4($s0) #Copy $v0 to $s0
	
	#Add ending NULL byte
	li $t0, 0x0 #Add 0 to $t0
	sb $t0, 5($s0) #Copy $t0 to $s0
	
	move $v0, $s0 #Move $v0 to $v0
	
	POP($s1) #Pop to get back $s1 from the stack
	POP($s0) #Pop to get back $s0 from the stack
	POP($ra) #Pop to get back $ra from the stack
	jr $ra #Return $ra
	nop
