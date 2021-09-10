  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,2		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here

  # Written 2021-09-07 by Julia Wang

# Inputs:
#	$a0 = input number where the 4 LSB specify a number
#	$v0 = Return, an ASCII code
hexasc:
	add $t0, $a0, $0 # or use move here to copy
	sll $t0, $t0, 28 # only want the last byte/4 bits
	move $t0, $t0 # setting the rest of the register to 0, alternatively use pseudo move
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
