// File name: ExtremeC_examples1_07.c
// Description: Conditional compilation.

#include "ExtremeC_examples1_08.h"
#include <stdio.h>
#include <stdlib.h>
#include "ExtremeC_examples1_08.h" // Test header guard from header file

#define INCREMENT

int main(int argc, char **argv) {
  say_hello();

  int i = 1;

#ifdef INCREMENT
  i++;
#else
  i--;
#endif

  printf("%d\n", i);

  return EXIT_SUCCESS;
}
