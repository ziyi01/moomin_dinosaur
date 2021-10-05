/*
 print-prime.c
 By David Broman.
  Last modified: 2021-09-23 by Amanda Hallstedt
 This file is in the public domain.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
int counter = 1;

void print_number(int printnum){
  printf("%10d", printnum);

  if(counter == 6){
        counter = 0;
        printf("\n");     
    }  
}


//parameter max is the largest number, our max
void print_sieves(int max){
    //create array and allocate memory on heap
    int *prime = (int *)malloc(sizeof(int)*(max+1));
	//int prime[max+1];

    //fill array with zeros, assuming all numbers are primes
    memset(prime, 0, sizeof(prime));
	
    //loop through numbers, starting on the lowest prime (2) and moving up.
    //stopping at sqaure root of max, since enough numbers should ahve been removed by then
	for(int i = 2; i*i <= max; i++)
	{
        //if number hasn't been marked as non-prime then check it
		if(prime[i] == 0)
		{
            //mark all multiples of the number as non-prime by assigning a 1
			for(int j = 2*i; j <=max ; j += i)
				prime[j] = 1;
		}
	}

    //loop through all numbers, only printing the ones marked as primes
    for(int i = 2; i <= max; i++){
        if(prime[i] == 0){
            print_number(i);
            counter ++;
        }
    }
    printf("\n");
    free(prime);
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

 
