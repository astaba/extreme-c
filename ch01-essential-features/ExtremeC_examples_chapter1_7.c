// File name: ExtremeC_exampels_chapter1_7.c
// Description: Example 1.7

#include "ExtremeC_examples_chapter1_8.h"
#include <stdio.h>
#include <stdlib.h>
#include "ExtremeC_examples_chapter1_8.h"

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
