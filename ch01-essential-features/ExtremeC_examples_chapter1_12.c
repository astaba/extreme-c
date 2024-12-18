// File name: ExtremeC_exampels_chapter1_12.c
// Description: Example 1.12

#include <stdio.h>

#define SIZE 5

int main(int argc, char **argv) {
  int arr[SIZE] = {9, 22, 30, 23, 18};
  /* arr[0] = 9;
  arr[1] = 22;
  arr[2] = 30;
  arr[3] = 23;
  arr[4] = 18; */

  //  int* ptr = &arr[0];
  int *ptr = arr;

  /*  for (;;) {
     printf("%d\n", *ptr);
     if (ptr == &arr[SIZE - 1]) {
       break;
     }
     ptr++;
   } */

  do {
    printf("%d\n", *ptr);
  } while (ptr++ != &arr[SIZE - 1]);

  return 0;
}
