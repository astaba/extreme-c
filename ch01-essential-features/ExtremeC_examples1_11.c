// File name: ExtremeC_examples1_11.c
// Description: Iterating over an array without pointer arithmetic

#include <stdio.h>

#define SIZE 5

int main(int argc, char** argv) {
 int arr[SIZE];
 arr[0] = 9;
 arr[1] = 22;
 arr[2] = 30;
 arr[3] = 23;
 arr[4] = 18;

 for (int i = 0; i < SIZE; i++) {
   printf("%d\n", arr[i]);
 }

 return 0;
}
