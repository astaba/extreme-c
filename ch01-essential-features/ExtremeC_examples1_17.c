// File name: ExtremeC_examples1_17.c
// Description: Passing by value vs passing by reference

#include <stdio.h>

void func(int a) {
  a = 5;
}

int main(int argc, char** argv) {
  int x = 3;
  printf("Before function call: %d\n", x);
  func(x);
  printf("After function call: %d\n", x);
  return 0;
}
