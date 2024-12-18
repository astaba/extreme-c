// File name: ExtremeC_exampels_chapter1_15.c
// Description: Dangling pointers

#include <stdio.h>
#include <stdlib.h>

int* create_an_integer(int default_value) {
  int var = default_value;
  return &var;
  // FIX: 
  // int *ptr = (int *)malloc(sizeof(int));
  // if (!ptr) {
  //   fprintf(stderr, "Memory allocation failed.\n");
  //   exit(EXIT_FAILURE);
  // }
  // *ptr = default_value;
  // return ptr;
}

int main() {
  int* ptr = NULL;
  ptr = create_an_integer(10);
  printf("%d\n", *ptr);
  // free(ptr);

  return 0;
}
