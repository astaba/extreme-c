// File name: ExtremeC_examples1_02.c
// Description: Defining a function like macro that accept arguments.

#include <stdio.h>

#define ADD(a, b) (a + b)

int main() {
  int x = 1;
  int y = 2;
  int z = ADD(x, y);

  printf("z = %d\n", z);
  return 0;
}
