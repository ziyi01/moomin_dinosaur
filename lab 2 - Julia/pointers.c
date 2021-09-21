#include <stdio.h>
#include <stdlib.h>

char count = 0;
char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

/* 80 bytes are reserved per list */
int* list2;
int* list1;

/*

*/
void copycodes(char* text, int* list, char* count){
  while(*text != 0) {
    *list = *text;
    list++;
    text++;
    (*count)++;
  }
}

/*

*/
void work(){
  list2 = (int*)calloc(80,sizeof(int));
  list1 = (int*)calloc(80,sizeof(int));
/* Loads addresses through putting pointers as parameters in copycodes*/
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
