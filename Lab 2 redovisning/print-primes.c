/*
 print-prime.c
 By David Broman.
 Last modified: 2021-09-22 by Julia Wang
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int placement = 0;

/*
  Print the input number with spacing and line breaks so that there are 6 columns
*/
void print_number(int n){
    printf("%d\t", n);
    placement++;
    
    if(placement == COLUMNS) {
      printf("\n");
      placement = 0;
    }
}

  /*  Uses Wilson's Theorem
    
    Parameter:
    int n = The number to check if prime
  */
int is_prime(int n){
  long factmod = 1;
  if(n > 1) {
    /* The factorial */
    for(int i = 1; i < n - 1; i ++) {
      /* Modulo during multiplication is equivalent to doing it later but it doesn't go past ridiculous numbers now */
      factmod = factmod * (n - i) % n; 
    }
    
    /* Check if modulo is n-1 */
    if(factmod == (n-1)) {
      return 1;
    }
  }
  return 0;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  /*
    Go through all values in range 2 to n to check if they're primes and then print
  */
  for(int i = 2; i <= n; i++) {
    if(is_prime(i) == 1) {
      print_number(i);
    }
  }
  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 
