/*
pointers.c
By Julia Wang
Last modified: 2021-09-24
*/

#include <stdio.h>
#include <stdlib.h>

char count = 0;
char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

/* 80 bytes are reserved per list */
int list1[20];
int list2[20]; // To heap alternative (int*)calloc(20,sizeof(int));  20 * 4 = 80 bytes

/*
copycodes()

Parameters:
text = pointer to the string that is input into the list
list = pointer to the list where the characters are stored into integers
c = pointer to the counter c which counts the amount of characters that are stored in all lists
*/
void copycodes(char* text, int* list, char* c){
  while(*text != 0) {
    *list = *text; // Dereferences to replace the value in the list with the character from text
    list++; // Increments the addresses to move to the next spot in the array and the string
    text++;
    (*c)++; // Gets the count value out and increments it
  }
}

/*
Loads addresses into copycodes() through putting pointers as parameters in the function
*/
void work(){
  copycodes(text1, list1, &count); 
  copycodes(text2, list2, &count);
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
