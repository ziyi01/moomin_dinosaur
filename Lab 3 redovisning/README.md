# Questions - Lab 3

## Assignment 1

- Test pressing BTN3 and BTN2 at the same time. What happens? Why?

They simultaneously update, the if statements registers if the buttons are pressed and stores this in a local variable and updates ``mytime`` together at the end. But you have to hold in the button as we can't customize the delay and it always has to run before button detection.

- Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR. Their functions are related. How? What are the differences?

**TRISE** is the register, the address to, which contains information about the direction (input/ouput) of PORTE.

**TRISESET** is a register that overwrites only the bits you store as "1" in TRISESET to "1" in TRISE, so you won't adjust other bits. 

**TRISECLR** is similar to TRISESET but sets TRISE to "0". CLR stands for CLEA(ne)R

- In the generated assembly code, in which MIPS register will the return values from functions getbtns and getsw be placed in. You should be able to answer this question without debugging the generated assembly code. 

Always in one of th v-registers, the return values. Since we only have one return value and 32 bits, it should return to v0. We compiled to double check, and it returned to $2 which according to MIPS reference sheet is v0.

- In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals. *Advice:* check the lecture slides from lecture 5 for ideas

Check where the pin leads, eg. RD9 leads to PORTD bit 9.

chipKIT™ Uno32™ Board Reference Manual page 11-13

chipKIT Basic I/O Shield reference manual page 8

## Assignment 2
- When the time-out event-flag is a "1", how does your code reset it to "0"?

We always check if a time-out occurs and puts the bit as 0, resetting the timer, if we detect such a flag.

- What would happen if the time-out event-flag was not reset to "0" by your code? Why?

There would be no delay for the timer to tick and increment timercount all the time as the timer is always done and won't run the rest of the code again.

- Which device-register (or registers) must be written to define the time between time-out events? Describe the function of that register (or of those registers).

``PRx`` where x is 2 for Timer 2. This is the 16-bit register where the period is defined, amount of cycles for the timer to tick.

- If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would that be easy to change? If so, how?



## Assignment 3
- When the time-out event-flag is a "1", how does your code reset it to "0"?


- What would happen if the time-out event-flag was not reset to "0" by your code? Why?

The code would be stuck at the ``user_ISR`` event.

- From which part of the code is the function ``user_isr`` called? Why is it called from there?

``_isr_trampoline`` in ``Vector.s`` is called anytime an interrupt occurs which ``jal user_isr``. The program jumps to the address 0x80000180 where the contents of vector.S are stored and runs the global routine ``_isr_trampoline``. EPC saves the address where the program was previously and jumps back after this.

- Why are registers saved before the call to ``user_isr``? Why are only some registers saved?

The callee-saved registers such as the s-registers are not saved as they are supposed to be handled by the handler, and restored by the routine it is jumped to. As an interrupt is an exception in the normal flow of the program all temporary variables that are usually seen as random values need to be returned when the program is resumed again.

- Which device-register (or registers), and which processor-register (or registers) must be written to enable interrupts from the timer? Describe the functions of the relevant registers.

The IEC and IPC-register is in the device which enables and sets the priority of Timer2. The processor register which is run through EI (rt?) sets the status of interrupts to enabled so that the Coprocessor (1?) will handle interrupts.