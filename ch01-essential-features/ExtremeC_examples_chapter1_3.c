// File name: ExtremeC_exampels_chapter1_3.c
// Description: Example 1.3

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
