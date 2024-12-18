// File name: ExtremeC_exampels_chapter1_2.c
// Description: Example 1.2

#include <stdio.h>

#define ADD(a, b) (a + b)

int main() {
  int x = 1;
  int y = 2;
  int z = ADD(x, y);

  printf("z = %d\n", z);
  return 0;
}