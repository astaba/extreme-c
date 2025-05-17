// File name: ExtremeC_examples1_01.c
// Description: Defining a macro

#include <stdio.h>
#include <stdlib.h>
#define ABC 5

int main(void) {
  int x = 2;
  int y = ABC;
  int z = x + y;

  printf("z = %d\n", z);

  return EXIT_SUCCESS;
}
