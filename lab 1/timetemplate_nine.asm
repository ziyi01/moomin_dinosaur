  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Modified 2021-09-08 by Julia Wang and Amanda Hallstedt
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
	.globl time2string
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
	li	$a0,20
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

# Assignment 3
#
# Parameters:
#	$a0 = $s0 = Address of an area in memory, suitably large for the output from the time2string
#	$a1 = $s1 = 16 LSB contains time-info, NBCD-coded of 4 bits for each number.
#	$s2 = counter
time2string:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	PUSH $s2
	# Move variables
	add $s0, $a0, $0
	add $s1, $a1, $0
	addi $s2, $0, 4

	# Check for nine
	add $t0, $s1, $0 # move time-info
	andi $t0, $t0, 15 # andi to remove the prior numbers
	addi $t1, $0, 9 # to compare to
	beq $t1, $t0, nine
	nop # in case of panic

	# Add end with a null-byte
	sb $0, 5($s0)
ascii_loop:
	# Fix arguments
	add $a0, $s1, 0
	jal hexasc 
	nop
	
	# Add number to memory
	add $t1, $s0, $s2 # calculate placement 
	sb $v0, ($t1)
	
	# Shift place
	srl $s1, $s1, 4

	# Check if-loop
	addi $t0, $0, 2
	addi $t1, $0, -1
	addi $s2, $s2, -1 # decrement counter for placement
	beq $s2, $t0, colon  # check if colon space
	nop
	bne $s2, $t1, ascii_loop # start over
	nop
time2end:
	POP $s2
	POP $s1
	POP $s0
	POP $ra
	jr $ra
	nop
colon:
	# Add colon
	add $t0, $0, 0x3A 
	add $t1, $s0, $s2
	sb $t0, ($t1)
	addi $s2, $s2, -1 # decrement counter for placement
	j ascii_loop
	nop
nine:
	# Add end with a null-byte
	sb $0, 8($s0)
	
	# sb all the letters
	addi $t0, $0, 0x45 # E
	addi $t1, $0, 0x4E # N
	addi $t2, $0, 0x49 # I
	addi $t3, $0, 0x4E # N
	
	sb $t0, 7($s0)
	sb $t1, 6($s0)
	sb $t2, 5($s0)
	sb $t3, 4($s0)
	
	# shift to next number
	srl $s1, $s1, 4
	
	addi $s2, $s2, -1 # decrement counter as the first "number" is placed
	j ascii_loop
	nop

# Inputs:
#	$a0 = input number where the 4 LSB specify a number
#	$v0 = Return, an ASCII code
hexasc:
	add $t0, $a0, $0 # or use move here to copy
	andi $t0, $t0, 0xF # remove all 1s except the ones at the end
	
	addi $t2, $0, 0xA # 0xA = 10, check if 0-9 or above 
	blt $t0, $t2, number
	nop
	
	j hexa_end
	addi $v0, $t0, 0x37
number:
	addi $v0, $t0, 0x30
hexa_end:		
	jr $ra
	nop

# Wait a number of milliseconds, specified by the parameter value.
# Assignment 4

# Parameters:
#	$a0 = $s0 = int ms
#	$t2 = int i	
delay: 
	PUSH $s0
	add $s0, $a0, $0 # move int ms to $s0
delay_while:
	# while( ms > 0 )
	addi $t1, $0, 1
	blt $s0, $t1, delay_end
	nop

	add $t2, $0, $0 # i = 0
# Executing the following for loop should take 1 ms
delay_for:
	# i < end value 
	addi $t0, $0, 5000 # change end value here (changed from original suggestion of 4711)
	addi $t2, $t2, 1 # i + 1
	bne $t2, $t0, delay_for
	nop

	# while( ms > 0 )
	addi $s0, $s0, -1 # ms = ms – 1;
	j delay_while
	nop
delay_end:
	POP $s0
	jr $ra
	nop
