// File name: ExtremeC_exampels_chapter1_10.c
// Description: Example 1.10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

  int i = 10;
  int *int_ptr = NULL;
  int_ptr = &i;

  char ch = 56;
  char *char_ptr = NULL;
  char_ptr = &ch;

  char *entry_1 = "Before pointer arithmetic";
  char *entry_2 = "After pointer arithmetic";

  printf("%s:\n\t%9s = %p\n\t%9s = %p\n", entry_1, "int_ptr", int_ptr,
         "char_ptr", char_ptr);

  int_ptr++;
  char_ptr++;

  printf("%s:\n\t%9s = %p\n\t%9s = %p\n", entry_2, "int_ptr", int_ptr,
         "char_ptr", char_ptr);

  return EXIT_SUCCESS;
}
