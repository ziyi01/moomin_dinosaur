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

void print_sieves(int max){    
  if(max < 2) {
      return;
  }

  /*  initialized with 0s, 0s are prime and 1s aren't
      numbers[0] is the same as the number 2
  */
  int numbers[max-2];

  /* Sieve */
  for(int i = 0; i < max-2; i++) {
    if(numbers[i] == 0) {
      for(int j = i+1; j < max-2; j++) {
        if((j+2) % (i+2) == 0) {
          numbers[j] = 1;
        } 
      }
    }
  }

  for(int k = 0; k < max-2; k++) {
    if(numbers[k] == 0) {
      print_number(k+2);
    }
  }
  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}