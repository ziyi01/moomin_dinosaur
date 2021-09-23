/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int placement = 0;

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
      factmod = factmod * (n - i) % n; /* Meowdulo */
    }
    
    /* Check if modulo is n-1 */
    if(factmod == (n-1)) {
      return 1;
    }
  } else if(n == 1) {
    return 1;
  }
  return 0;
}

void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  if(n == 2) {
    print_number(2);
    printf("\n");
    return;
  } else if(n < 2) {
    return;
  }

  for(int i = 2; i < n; i++) {
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

 
