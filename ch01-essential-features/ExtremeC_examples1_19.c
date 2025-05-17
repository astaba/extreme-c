// File name: ExtremeC_examples1_19.c
// Description: Function pointers

#include <stdio.h>
#include <stdlib.h>

int sum(int a, int b) { return a + b; }

int substract(int a, int b) { return a - b; }

int main(int argc, char **argv) {
  int (*funct_ptr)(int, int) = NULL;

  int a = 9;
  int b = 13;

  funct_ptr = &sum;
  printf("a + b = %d\n", funct_ptr(a, b));

  funct_ptr = &substract;
  printf("a - b = %d\n", funct_ptr(a, b));

  return EXIT_SUCCESS;
}
