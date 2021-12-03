  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

	.data
	.globl time2string
	.globl delay
	.globl led_test
	.globl enable_interrupt
	.text
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

	# Add end with a null-byte
	sb $0, 5($s0)
ascii_loop:
	# Fix arguments
	add $a0, $s1, 0 # borde vara fine att sätta efter
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
	addi $s2, $s2, -1 # decrement i, no need for nop
	beq $s2, $t0, colon
	nop
	bne $s2, $t1, ascii_loop
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
	addi $s2, $s2, -1 # decrement i
	j ascii_loop
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
  # Written 2021-09-07 by Julia Wang

# Assignment 2

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
	move $s0, $a0 # move int ms to $s0
delay_while:
	# while( ms > 0 )
	beq $s0, $0, delay_end

	add $t2, $0, $0 # i = 0
# Executing the following for loop should take 1 ms
delay_for:
	# Do nothing.
	
	# i < 4711
	addi $t0, $0, 6600 # change 4711 here
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

# Lab 3 - Assignment 3 g)
enable_interrupt:
	ei
	jr $ra
	nop