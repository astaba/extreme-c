// File name: ExtremeC_exampels_chapter4_8.c
// Description: Dynamic memory allocation. Pointer variable, while allocated on
// the stack frame of the main() function, pointed out to heap memory adresse.

#include <stdio.h>  // For printf function
#include <stdlib.h> // For malloc and free function

void fill(char *ptr) {
  ptr[0] = 'H';
  ptr[1] = 'e';
  ptr[2] = 'l';
  ptr[3] = 'l';
  ptr[5] = 0;
}

int main(int argc, char **argv) {
  void *gptr = malloc(10 * sizeof(char));
  char *ptr = (char *)gptr;
  fill(ptr);
  printf("%s!\n", ptr);
  free(ptr);
  return 0;
}
