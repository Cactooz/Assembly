.text

addi $a0, $0, 4 #Add the number for doing factorial with to $a0

addi $a2, $0, 1 #Set $a2 to 1
addi $v0, $0, 1 #Set output $v0 to 1
addi $v1, $a0, 1 #Set $v1 to $a0+1

loop:
	add $a1, $v0, $0 #Set $a1 to $v0
	addi $a2, $a2, 1 #Increment $a2 with 1 ($a2++)
	beq $a2, $v1, stop #If $a2 = $v1 we are done with the calcluations
	add $0, $0, $0 #NOP

	add $at, $a2, $0 #Set $at to $a2, because we don't want to modify $a2
	add $a3, $a1, $a1 #Add $a1 twice
	addi $at, $at, -2 #Remvoe 2 from $at because we did 2 additions
	for:
		beq $at, $0, save #Break out of the loop if the additions are done
		add $0, $0, $0 #NOP
		add $a3, $a3, $a1 #Add $a1 to $a3 once
		addi $at, $at, -1 #Remove 1 from $at ($a3--)
		beq $0, $0, for #Go back to the start of the loop
		add $0, $0, $0 #NOP
	save:
		add $v0, $a3, $0 #Move the result from $a3 to $v0
		beq $0, $0, loop #Go back to the  loop
		add $0, $0, $0 #NOP

stop:
	beq $0, $0, stop #Infinte stop loop
	add  $0, $0, $0 #NOP
