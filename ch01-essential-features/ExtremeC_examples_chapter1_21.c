// File name: ExtremeC_exampels_chapter1_21.c
// Description: Memory layout

#include <stdio.h>
#include <stdlib.h>

typedef struct sample {
  char first;
  char second;
  char third;
  short fourth;
} sample_t;

void print_size(sample_t *var) { printf("Size: %lu bytes\n", sizeof(*var)); }

void print_bytes(sample_t *var) {
  unsigned char *ptr = (unsigned char *)var;
  for (int i = 0; i < sizeof(*var); i++) {
    printf("Byte Index %d: %d\n", i, *ptr++);
  }
}

int main(int argc, char **argv) {
  sample_t *test;
  test->first = 'A';
  test->second = 'B';
  test->third = 'C';
  test->fourth = 520;

  print_size(test);
  print_bytes(test);

  return EXIT_SUCCESS;
}
