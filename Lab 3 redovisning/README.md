# Questions - Lab 3

## Assignment 1

- Test pressing BTN3 and BTN2 at the same time. What happens? Why?

They simultaneously update, the if statements registers if the buttons are pressed and stores this in a local variable and updates ``mytime`` together at the end. But you have to hold in the button as we can't customize the delay and it always has to run before button detection.

- Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR. Their functions are related. How? What are the differences?

**TRISE** is the register, the address to, which contains information about the direction (input/ouput) of PORTE.

**TRISESET** 


- In the generated assembly code, in which MIPS register will the return values from functions getbtns and getsw be placed in. You should be able to answer this question without debugging the generated assembly code. 

Always in one of th v-registers. Since we only have one return value and 32 bits, it should return to v0. We compiled to double check, and it returned to $2 which according to mips reference sheet is v0.


- In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals. *Advice:* check the lecture slides from lecture 5 for ideas

chipKIT™ Uno32™ Board Reference Manual sida 11-13


## Assignment 2
- When the time-out event-flag is a "1", how does your code reset it to "0"?

We always check if a time-out occurs and puts the bit as 0, resetting the timer, if we detect such a flag.

- What would happen if the time-out event-flag was not reset to "0" by your code? Why?

There would be no delay for the timer to tick and update all the time as the timer is always done and doesn't count again.

- Which device-register (or registers) must be written to define the time between time-out events? Describe the function of that register (or of those registers).


- If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would that be easy to change? If so, how?



## Assignment 3
- When the time-out event-flag is a "1", how does your code reset it to "0"?


- What would happen if the time-out event-flag was not reset to "0" by your code? Why?

The code would be stuck at the ``user_ISR`` event.

- From which part of the code is the function ``user_isr`` called? Why is it called from there?



- Why are registers saved before the call to ``user_isr``? Why are only some registers saved?


- Which device-register (or registers), and which processor-register (or registers) must be written to enable interrupts from the timer? Describe the functions of the relevant registers.
