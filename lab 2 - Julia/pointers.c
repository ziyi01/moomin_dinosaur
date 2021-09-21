#include <stdio.h>

int count = 0;

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

/* 80 bytes are reserved per list, with 2 bytes aligned (padding) */
int* list1;
int* list2;

/*


Are the variables supposed to be named like this?

Parameters:
  $a0 = text1
  $a1 = list1
  $a2 = count
*/
void copycodes(char* a0, int* a1, int a2){
  int t0 = *a0 & 0xFF; /* Use AND-mask to get the LSB byte from $a0, lb, maybe should be a pointer instead???? */
  
  while(1) {
    if(t0 == 0){ /* Branch if equal*/
      return;
    }

    t0 = a1;
    *a0 ++;
    *a1 += 4;

    int t1 = a2 & 0xFFFFFFFF; /* lw $t1, 0($a2)*/
    t1 ++;
    a2 = t1;
  }
}

/*

*/
void work(){
  copycodes(text1, list1, count); /* Loads addresses through putting them as parameters in copycodes*/
  copycodes(text2, list2, count);
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
