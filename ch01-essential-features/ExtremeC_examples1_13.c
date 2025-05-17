// File name: ExtremeC_examples1_13.c
// Description: Example 1.13
// Generic pointers

#include <stdio.h>

int main(int argc, char **argv) {
  int var = 9;
  int *ptr = &var;
  void *gptr = ptr;

  // ERROR:
  printf("%d\n", *gptr);
  // FIX: Cast before dereferencing: *(int *)gptr;
  /* printf("%d\n", *(int *)gptr); */

  return 0;
}
