.text

addi $a0, $0, 8 #Add the number for doing factorial with to $a0

addi $a2, $0, 1 #Set $a2 to 1
addi $v0, $0, 1 #Set output $v0 to 1
addi $v1, $a0, 1 #Set $v1 to $a0+1

loop:
	add $a1, $v0, $0 #Set $a1 to $v0
	addi $a2, $a2, 1 #Increment $a2 with 1 ($a2++)
	beq $a2, $v1, stop #If $a2 = $v1 we are done with the calcluations
	add $0, $0, $0 #NOP
	mul $v0, $a1, $a2 #Multiply $a1 and $a2
	beq $0, $0, loop #Go back to the loop start
	add $0, $0, $0 #NOP

stop:
	beq $0, $0, stop #Infinte stop loop
	add  $0, $0, $0 #NOP
