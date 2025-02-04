// File name: ExtremeC_examples_chapter5_1.c
// Description: Example 5.1

/* int main(int argc, char** argv) {
  char arr[4];
  arr[0] = 'A';
  arr[1] = 'B';
  arr[2] = 'C';
  arr[3] = 'D';
  return 0;
} */

#include <stdio.h>
#include <string.h>

int main(void) {
  char buffer[10] = {0};
  int important_data = 23;

  // BUG: Stack smashing
  // strcpy(buffer, "abcdefghijklmnopqrs");

  // FIX:
  strncpy(buffer, "abcdefghijklmnopqrs", strlen(buffer));

  printf("Important data: %d\n", important_data);

  return 0;
}
