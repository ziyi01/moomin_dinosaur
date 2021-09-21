/*
 prime.c
 By David Broman & Julia Wang
 Last modified: 2021-09-17
 This file is in the public domain.
*/

#include <stdio.h>

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

int main(void) {
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
