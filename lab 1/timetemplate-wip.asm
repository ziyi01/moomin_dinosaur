  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Modified 2021-09-08 by Julia Wang
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

# Parameters:
#	$a0 = $s0 = Address of an area in memory, suitably large for the output from the time2string
#	$a1 = $s1 = 16 LSB contains time-info, NBCD-coded of 4 bits for each number.
#	$s2 = counter
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	PUSH $s2
	PUSH $s3
	
	add $t4, $0, $a0
	
	add $s0, $0, $a0
	add $s1, $a1, $0
	addi $s2, $0, 5 # i = 5
	
	# end with a null(zero)-byte
	add $s3, $s0, $s2
	sb $0, ($s3)
	subi $s2, $s2, 1 # i = 4
ascii_loop:
	# fix arguments
	add $a0, $s1, $0
	jal hexasc
	
	# add to memory
	add $t0, $v0, $0
	add $s3, $s0, $s2 # calculate placement 
	sb $t0, ($s3)
	
	# Loop
	# shift place
	srl $s1, $s1, 4 # Shift to check the next number, skipped in colon so shouldn't matter
	
	subi $s2, $s2, 1 # decrement i
	addi $t0, $0, 2
	addi $t1, $0, -1
	beq $s2, $t0, colon # inefficient, everytime
	nop # in case
	bne $s2, $t1, ascii_loop # loop again, check for new number
	nop
	
	j end
colon:
	# add colon to the memory address
	add $t0, $0, 0x3A
	add $s3, $s0, $s2
	sb $t0, ($s3)
	
	subi $s2, $s2, 1 # decrement i
	j ascii_loop
end:
	POP $s3
	POP $s2	
	POP $s1
	POP $s0
	POP $ra
	jr $ra

  # you can write your code for subroutine "hexasc" below this line
  #
  # Written 2021-09-07 by Julia Wang

# Inputs:
#	$a0 = input number where the 4 LSB specify a number
#	$v0 = Return, an ASCII code
hexasc:
	add $t0, $a0, $0
	sll $t0, $t0, 28 # only want the last byte/4 bits
	add $t0, $t0, $0 # setting the rest of the register to 0
	srl $t0, $t0, 28
	
	addi $t2, $0, 0xA	
	blt $t0, $t2, number
	
	addi $v0, $t0, 0x37

	j hexa_end
number:
	addi $v0, $t0, 0x30
	j hexa_end
hexa_end:		
	jr $ra

# Wait a number of milliseconds, specified by the parameter value.
# Assignment 4, WIP

# Parameters:
#	$a0 = $s0 = int ms
#	$s1 = int i	
delay: 
	PUSH $s0
	PUSH $s1
	move $s0, $a0
	
	sgt $t0, $s0, $0
	bne $t0, $0, delay_loop
	nop
	
	j delay_end
	
delay_while:
	# ms = ms – 1;
	subi $s0, $s0, 1
	
	# Executing the following for loop should take 1 ms
	# for( i = 0; i < 4711; i = i + 1 ) /* The constant 4711 must be easy to change! */
	addi $s1, $0, $0
delay_for:
	
	# Do nothing.
	
	addi $s1, $s1, 1 # i + 1
	sgt

	# while( ms > 0 )
	sgt $t0, $s0, $0
	beq $t0, $0, delay_loop

	POP $s0
	jr $ra
	nop

delay_end