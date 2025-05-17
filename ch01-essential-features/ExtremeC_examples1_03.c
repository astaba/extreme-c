// File name: ExtremeC_examples1_03.c
// Description: Using macro to create a Domain Specific Language (DSL)

#include <stdio.h>
#include <stdlib.h>

#define LOOP(c, i, l) for (int c = i; c < l; c++) {
#define ENDLOOP }
#define PRINTF(v) printf("counter = %d\n", v)

int main(void) {
  // clang-format off
  LOOP(counter, 0, 5)
    PRINTF(counter);
  ENDLOOP
  // clang-format on
  return EXIT_SUCCESS;
}
