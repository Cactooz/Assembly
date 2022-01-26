  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro PUSH (%reg)
	addi $sp,$sp,-4
	sw %reg,0($sp)
.end_macro

.macro POP (%reg)
	lw %reg,0($sp)
	addi $sp,$sp,4
.end_macro

	.data
	.align 2
	
mytime: .word 0x5957

timstr: .ascii "text more text lots of text\0"
	.text
	
main:
	# print timstr
	la $a0,timstr
	li $v0,4
	syscall
	nop
	# wait a little
	li $a0,2
	jal delay
	nop
	# call tick
	la $a0,mytime
	jal tick
	nop
	# call your function time2string
	la $a0,timstr
	la $t0,mytime
	lw $a1,0($t0)
	jal time2string
	nop
	# print a newline
	li $a0,10
	li $v0,11
	syscall
	nop
	# go back and do it all again
	j main
	nop
# tick: update time pointed to by $a0

tick:	lw $t0,0($a0)			# get time
	addiu $t0,$t0,1		# increase
	andi $t1,$t0,0xf		# check lowest digit
	sltiu $t2,$t1,0xa		# if digit < a, okay
	bnez $t2,tiend
	nop
	addiu $t0,$t0,0x6		# adjust lowest digit
	andi $t1,$t0,0xf0		# check next digit
	sltiu $t2,$t1,0x60		# if digit < 6, okay
	bnez $t2,tiend
	nop
	addiu $t0,$t0,0xa0		# adjust digit
	andi $t1,$t0,0xf00		# check minute digit
	sltiu $t2,$t1,0xa00		# if digit < a, okay
	bnez $t2,tiend
	nop
	addiu $t0,$t0,0x600	# adjust digit
	andi $t1,$t0,0xf000		# check last digit
	sltiu $t2,$t1,0x6000		# if digit < 6, okay
	bnez $t2,tiend
	nop
	addiu $t0,$t0,0xa000	# adjust last digit
	
tiend:	sw $t0,0($a0)		# save updated result
	jr $ra				# return
	nop
	
  # you can write your code for subroutine "hexasc" below this line
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

delay:
	jr $ra
	nop
	
time2string:
	PUSH($ra) #Push $ra to the stack
	PUSH($s0) #Push $s0 to the stack
	PUSH($s1) #Push $s1 to the stack
	
	#Save $a0 to $s1
	move $s0, $a0
	
	#Mm:ss
	move $s1, $a1 #Save $a1 to $s1
	srl $t1, $s1, 12 #Shift 12 steps to the right
	and $t1, $t1 0x0F #Mask out all except the four LSb
	move $a0, $t1 #Move $s1 to $a0
	
	jal hexasc #Go to hexasc
	nop
	
	sb $a0, 0($s0) #Copy $a0 to $s0
			
	POP($s1) #Pop to get back $s1 from the stack
	POP($s0) #Pop to get back $s0 from the stack
	POP($ra) #Pop to get back $ra from the stack
	jr $ra #Return $ra
