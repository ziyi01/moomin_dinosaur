# Questions - Lab 2

## Assignment 2

- What does it mean when a function does not return a value? How do you state that in a program? How can then the function (or more precisely, the procedure)  perform anything useful?

This is written by appending a function with ``void`` as return type. The function will return control to the caller without returnning a value.

The function can instead modify other (multiple) values outside of the local scope by using pointers.

- How did you implement the side effect that is needed to make print_number behave correctly?

An extra global variable is added to keep count of the columns. ``int placement = 0;`` 

## Assignment 3

- How did you represent the marking of 'prime' and 'not a prime' in the memory array?

As an heap is initialized with `0s` by default (otherwise I need to fill the array), I set it to represent that a number is either a prime number or not checked yet. So if ``numbers[5] == 0`` in the end of the program then it means that ``(5+2 =) 7`` is a prime number. And the reverse for `not a prime`.

- Which are the main steps in the algorithm? How have you implemented these steps?

The main steps are:

1. Initialization
2. Sieve through every number `i` in the array marked prime from bottom up (2 to n).
   1. For this number `i` check if the higher numbers `j` are divisible by `i`. 
   2. Mark if a number is divisible, by setting it as 1 in the array
3. Go through the numbers array and print the ones set to `0`, the prime numbers

- What is the largest prime number that you can prime within 2 seconds of computation? What is the largest number you can print within 10 seconds? Is it the same for `print_prime.c`, `sieves.c` and `sieves-heap.c`? Why or why not?

For `print_prime.c`:

- 2 seconds, ~18 000
- 10 seconds, ~40 000


For `sieves.c`:

- 2 seconds, ~120 000
- 10 seconds, ~300 000

For `sieves-heap.c`:

- 2 seconds, ~120 000
- 10 seconds, ~300 000

Possibly a bit slower actually on the heap.

**Difference in Wilsons and Sieve:**

Quicker to print sieve as it just sifts through the array but the operations to check if it is prime needs to be run every time for Wilson's when printing multiple numbers.

**Difference in heap and stack:**
This is because a heap is less efficient as the space is managed manually and allocated first and also required de-allocation later. The space is put in a random order and costs more, like with arrays and trees, but is more dynamic. Slow access time.

## Assignment 4
- Explain how you get the pointer addresses to the two char arrays (`text1` and `text2`) and the counter variable (`count`) in the function `work()`.

`char* text1, text2` and `int count` is defined globally and as such is defined in all scopes which is how you can input it as a parameter through work().

- What does it mean to increment to a pointer? What is the difference between incrementing the pointer that points to the ASCII text string, and incrementing the pointer that points to the integer array? In what way is the assembler code and the C code different?

Incrementing the pointer moves the pointer to the next `object` in memory, which means that it moves the amount of bits equal to `the size of the data type` it is a pointer of. For an integer pointer, if the address is incremented one step that means that it actually moves `32 bits` in C.

In MIPS, incrementing the address one step means to move the pointer with one byte solely as there is no defined data types and the address is divided into 4 (4 bytes = 1 word).

- What is the difference between incrementing a pointer and incrementing a variable that a pointer points to? Explain how your code is incrementing the count variable.

Incrementing a pointer, increases the address and makes it point to the next value. Incrementing the value means that you are still pointing at the same space in memory and just adjusting the value that the address is pointing to, you're not at the next spot in memory.

My code increments the count variable by inputting a pointer of the counter to `copycodes(...)` and dereferencing the pointer to access the value it is pointing at and incrementing that value.

- Explain a statement in your code where you are dereferencing a pointer. What does this mean? Explain by comparing with the corresponding assembler code.

``*list = *text``, where we dereference both the pointers list and text. It means to replace the value ``list`` was pointing to with the value ``text`` was pointing to. The equivalent operation in assembler code is to load the value with an operation such as `lb` from the address ``text`` and saving it with a command as `sb` to the address ``list``.

- Is your computer using big-endian or little-endian? How did you come to your conclusion? Is there any benefit of using either of the two alternatives?

C uses little-endian. The benefit this brings is that it's easier to judge if a number is odd or even also it's easier to increase values. An example is if you add two numbers in a big-endian number all bits need to be moved up but for little-endian, the LSB stay and the new numbers are shifted to the right at a higher address instead. It's simpler to perform operations.

## Assignment 5
- Consider `AM18`, `AM19` and `AF1`. Explain why `gv` ends up with the incremented value, but `m` does not.

You input the value of `m` into `fun()` as a parameter, this doesn't adjust the actual value of `m` and just copies it and increments it as another variable. This replaces the value in `gv` which is a global variable and can be accessed from anywhere.

- Pointer `cp` is a character pointer that points to a sequence of bytes. What is the size of the `cp` pointer itself?

This operation is the same as ``char *cp = "Bonjour!";``. The pointer is 4 bytes as an address is 32 bits and every char is one byte. As such the total amount of memory allocated is ``4 + 8 + 1`` bytes. 

- Explain how a C string is laid out in memory. Why does the character string that `cp` points to have to be 9 bytes?

It is 8 characters, and thus 8 bytes and ends with a null character, a zero-byte. ``8+1`` bytes.

- Which addresses have `fun` and `main`? Which sections are they located in? What kind of memory are they stored in? What is the meaning of the data that these symbols points to? 

fun: ``0x9D001180``

main: ``0x9D0011D8`` 

Both are within the range of the **Program flash** in the Virtual Memory Map which represents the space between ``0x9D000000`` and ``0x9D007FFF``.

It only exists under the runtime and is deleted after???.

***Before the examination***

- Which addresses are variables in and gv located at? Which memory sections according to the PIC32 memory map? Why?

in: ``0xA0000008``

gv: ``0xA000000C`` 

In RAM, stores (global) variables indefinitely till the program is exited. Every "minnescell" is CAPABLE OF BEING DIRECTLY ACCESSED?!1111

- Variables p and m are not global variables. Where are they allocated? Which memory section is used for these variables? Why are the address numbers for p and m much larger than for in and gv?

p: ``0xA0003FE8``
m: ``0xA0003FE4``

In the reserved blocks for temporary memory.

- At print statement AM5, what is the address of pointer p, what is the value of pointer p, and what value is pointer p pointing to?

``0xA0003FE8`` and ``0xA0003FE4``, it's pointing at the temporary variable `m`.

- At print statement AM7, what is the address of pointer p, what is the value of pointer p, and what value is pointer p pointing to?

Same as the previous question, only the value of m has been adjusted not the pointer p.

- Consider AM14 to AM17. Is the PIC32 processor using big-endian or little-endian? Why?

Little-endian the LSB is at the right side, as it increments from the right bits as it increases in address.