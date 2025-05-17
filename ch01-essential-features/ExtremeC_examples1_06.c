// File name: ExtremeC_examples1_06.c
// Description: Using variadic macro to repeat instructions.

#include <stdio.h>
#include <stdlib.h>

#define LOOP_3(X, ...) printf("%s\n", #X);
#define LOOP_2(X, ...)                                                         \
  printf("%s\n", #X);                                                          \
  LOOP_3(__VA_ARGS__)
#define LOOP_1(X, ...)                                                         \
  printf("%s\n", #X);                                                          \
  LOOP_2(__VA_ARGS__)
#define LOOP(...) LOOP_1(__VA_ARGS__)

int main(int argc, char **argv) {

  LOOP(Ava Love Lace)
  LOOP(Ava, Lovelace)
  LOOP(Ava, Love, Lace, AndMoore)

  return EXIT_SUCCESS;
}
