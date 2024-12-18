// File name: ExtremeC_exampels_chapter1_20.c
// Description: Define type aliases for function pointers

#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool_t;
typedef bool_t (*less_than_funct_t)(int, int);

bool_t less_than(int a, int b) {
  bool_t output = a < b ? true : false;
  return output;
}

bool_t less_than_modular(int a, int b) {
  bool_t output = (a % 5) < (b % 5) ? true : false;
  return output;
}

int main(int argc, char **argv) {
  less_than_funct_t funct_ptr = NULL;

  int a = 54;
  int b = 61;
  bool_t result;

  funct_ptr = &less_than;
  result = funct_ptr(a, b);
  printf("%d < %d is %s\n", a, b, result ? "true" : "false");

  funct_ptr = &less_than_modular;
  result = funct_ptr(a, b);
  printf("(%d %% 5) < (%d %% 5) is %s\n", a, b, result ? "true" : "false");

  return EXIT_SUCCESS;
}
