# Computes factorial number n!
# Parameter: $a0 = n 

# Example: 5!
# 5*4 = 4+4+4+4+4 = 20
# 3*20 = 20+20+20 = 60
# 2*60 = 60+60 = 120

.text

addi $a0, $0, 0 # set n

beq $a0, $0, zero

addi $a1, $a0, -1 # set n-1
addi $a2, $a0, 0 # counter
addi $a0, $a0, -1 # as a1 occupies n-1
addi $v0, $0, 0 # clear $v0

multiplication:
add $v0, $v0, $a1
addi $a2, $a2, -1 # count

beq $a2, 0, next # check if counter = 0
add $0, $0, $0 # NOP
beq $0, $0, multiplication
add $0,$0,$0 # NOP	

next:
addi $a0, $a0, -1 # next
addi $a1, $v0, 0 # multiply with previous result
addi $a2, $a0, -1 # new counter

beq $a0, 1, done
add $0, $0, $0 # NOP
beq $0, $0, multiplication
add $0, $0, $0 # NOP

zero:
addi $v0, $0, 1

done:
beq $0, $0, done # stop loop