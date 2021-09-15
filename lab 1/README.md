# Questions for lab 1

## Assignment 1
- Which lines of had to be changed? Why?

At the branch where they check to stop or not. So either the limit where they stop or the comparison with the value of $s0 if it's greater than $t0.

## Assignment 2
- If the argument is 17, what is the return-value? Why?

1, since `17` in decimal becomes `1 0001` in binary, which means that the first bit (which was worth 16) is ignored as the method only processes the **4 LSB**.

- If your solution contains a conditional-branch instruction: which input values cause the instruction to actually branch to another location?

We compare the 4 digits with `OxA` to see if they are "0-9" and then input the T/F value into the branch (or directly use blt)

## Assignment 3
- Which registers are saved and restored by your subroutine? Why?



- Which registers are used but not saved? Why are these not saved?

All the $t registers and the $v ones as they are supposed to be "garbage" after using them. They are temporary registers used to store temporary values.

- Assume the time is 16:53. Which lines of your code handle the '5'? 


## Assignment 4
- If the argument value in register $a0 is zero, which instructions in your subroutine are executed? How many times each? Why?



- If the argument value in register $a0 is zero, which instructions in your subroutine are executed? How many times each? Why?



## Assignment 6
- What is the effect of the assembler directive .global? Why is the directive particularly important in this assignment?

Makes the subroutine (the one labeled) available to files outside of the one where it is defined.

## Assignment 7
- When you move your code from the simulator to the lab-board, you have to change the value of the constant in the delay subroutine to get correct timing. Why?

BECAUSE ITS A FUCKING CHIPKIT