# Questions for lab 1

## Assignment 1
- Which lines of had to be changed? Why?

At the branch where they check to stop or not. So either the limit where they stop or the comparison with the value of $s0 if it's greater than $t0.

## Assignment 2 - hexasc
- If the argument is 17, what is the return-value? Why?

1, since `17` in decimal becomes `1 0001` in binary, which means that the first bit (which was worth 16) is ignored as the method only processes the **4 LSB**.

- If your solution contains a conditional-branch instruction: which input values cause the instruction to actually branch to another location?

We compare the 4 digits with `OxA` to see if they are "0-9" and then input the True/False (1/0) value into the branch (or directly use blt that is a pseudo instruction of this).

## Assignment 3 - time2string
- Which registers are saved and restored by your subroutine? Why?

$ra and $s0-2 are saved and then restored.

``$ra`` needs to be restored as we ``jal`` to the ``hexasc`` method which overwrites the return address and we need it to later jump back to main.

``$s0`` saves the argument of ``$a0`` (the address) as the register $a0 will be used in other subroutines and the address is used throughout the whole time2string.

``$s1`` saves the argument of ``$a1`` (time-info) as the register $a1 might be used in another subroutine, we know it won't but it's not wrong to assume the opposite, and this time-info is used throughout the routine.

``$s2`` is used as a counter to count the amount of times for the loop to run and also to calculate the placement of addresses throughout the routine which means it can't be overwritten and needs to be saved if another subroutine accesses the register.

(Antar att det är det här de menar med saved and restored?)

- Which registers are used but not saved? Why are these not saved?

All the $t registers and the $v ones as they are supposed to be "garbage" after using them. They are temporary registers used to store temporary values.

- Assume the time is 16:53. Which lines of your code handle the '5'? 

line 89,90 and 96-101 adjusts the time-info, processes it and stores the byte at the assigned address.

MIGHT NOT BE CORRECT? CUZ CHANGES

## Assignment 4 - delay
- If the argument value in register $a0 is zero, which instructions in your subroutine are executed? How many times each? Why?

The comparison is run between the argument and $0 which branches to the end.

- If the argument value in register $a0 is -1, which instructions in your subroutine are executed? How many times each? Why?

Same thing as if the register was zer0

## Assignment 6 - make 
- What is the effect of the assembler directive .global? Why is the directive particularly important in this assignment?

Makes the subroutine (the one labeled) available to files outside of the one where it is defined.

## Assignment 7 - make install
- When you move your code from the simulator to the lab-board, you have to change the value of the constant in the delay subroutine to get correct timing. Why?

BECAUSE ITS A FUCKING CHIPKIT