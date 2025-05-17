// File name: ExtremeC_examples1_12.c
// Description: Using pointer arithmetic to iterate over an array

#include <stdio.h>

#define SIZE 5

int main(int argc, char **argv) {
  int arr[SIZE] = {9, 22, 30, 23, 18};

  //  int* ptr = &arr[0];
  int *ptr = arr;

  /*  for (;;) {
     printf("%d\n", *ptr);
     if (ptr == &arr[SIZE - 1]) {
       break;
     }
     ptr++;
   } */

  while (ptr != &arr[SIZE]) {
    printf("%d\n", *ptr++);
  }

  return 0;
}
