/*
 prime.c
 By David Broman.
 Last modified: 2021-09-21 by Amanda Hallstedt
 This file is in the public domain.
*/


#include <stdio.h>

//checks if number is prime or not using Wilson's method

int is_prime(int n){
   int fact = 1;
  for (int i = 1; i < n; i++)
  {
    fact = fact * i % n;
  }
  
  if (n == 2){
    return 1;
  }

  else if (fact == (n - 1)) {
    return 1;
  }
  
  return 0;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
