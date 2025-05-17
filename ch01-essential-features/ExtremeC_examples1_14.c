// File name: ExtremeC_examples1_14.c
// Description: Generic pointers to create a generic function.

#include <stdio.h>
#include <stdlib.h>

void print_bytes(void *data, size_t data_size) {
  // unsigned char is the most appropriate data type
  // for surfing on the memory bytewise
  unsigned char *ptr = data;

  for (int i = 0; i < data_size; i++) {
    printf(" 0x%-4x ", *ptr++);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  int a = 4;
  double b = 24.01;

  print_bytes(&a, sizeof(int));
  print_bytes(&b, sizeof(double));

  return EXIT_SUCCESS;
}
