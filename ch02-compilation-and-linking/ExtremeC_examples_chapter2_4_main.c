// File name: ExtremeC_examples_chapter2_4_main.c
// Description: This file contains the 'main' function.

#include <stdio.h>
#include "ExtremeC_examples_chapter2_4_decls.h"

int main(int argc, char** argv) {
  int x = add(4, 5);
  int y = multiply(9, x);
  printf("y = %d\n", y);
  return 0;
}
