// File name: ExtremeC_examples_chapter2_5_main.c
// Description: Linker can be fooled: This file contains the 'main' function and
// a call to the add() defined nowhere but has an "overload function" with a
// distinct defenition.

#include <stdio.h>

int add(int, int);

int main(int argc, char **argv) {
  int x = add(5, 6);
  printf("Result: %d\n", x);
  return 0;
}
