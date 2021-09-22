# Questions - Lab 2

## Assignment 2

- What does it mean when a function does not return a value? How do you state that in a program? How can then the function (or more precisely, the procedure)  perform anything useful?

This is written by appending a function with ``void`` as return type. The function will return control to the caller without returnning a value.

The function can instead modify other (multiple) values outside of the local scope by using pointers.

- How did you implement the side effect that is needed to make print_number behave correctly?

An extra global variable is added to keep count of the columns. ``int placement = 0;`` 

## Assignment 3

- How did you represent the marking of 'prime' and 'not a prime' in the memory array?

As an array is initialized with `0s` by default, I set it to represent that a number is either a prime number or not checked yet. So if ``numbers[5] == 0`` in the end of the program then it means that ``(5+2 =) 7`` is a prime number. And the reverse for `not a prime`.

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

**Difference in Wilsons and Sieve:**

Quicker to print sieve as it just sifts through the array but the operations to check if it is prime needs to be run every time for Wilson's when printing multiple numbers.

**Difference in heap and stack:**


## Assignment 4
- Explain how you get the pointer addresses to the two char arrays (`text1` and `text2`) and the counter variable (`count`) in the function `work()`.

`char* text1, text2` and `int count` is defined globally and as such is defined in all scopes.

- What does it mean to increment to a pointer? What is the difference between incrementing the pointer that points to the ASCII text string, and incrementing the pointer that points to the integer array? In what way is the assembler code and the C code different?



- What is the difference between incrementing a pointer and incrementing a variable that a pointer points to? Explain how you code is incrementing the count variable.


- Explain a statement in your code where you are dereferencing a pointer. What does thie mean? Explain by comparing with the corresponding assembler code.


- Is your computer using big-endian or little-endian? How did you come to your conclusion? Is there any benefit of using either of the two alternatives?


## Assignment 5
- Consider `AM18`, `AM19` and `AF1`. Explain why `gv`ends up with 