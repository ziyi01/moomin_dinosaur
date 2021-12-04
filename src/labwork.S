  # labwork.S
  # Written 2021 by Julia Wang
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

	.data
	.globl delay
	.text

# Wait a number of milliseconds, specified by the parameter values

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