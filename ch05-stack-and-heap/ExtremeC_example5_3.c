// File name: ExtremeC_examples_chapter5_3.c
// Description: Example 5.3

#include <stdio.h>
#include <stdlib.h>

void print_mem_map() {
#ifdef __linux__
  FILE *fp = fopen("/proc/self/maps", "r");
  if (!fp) {
    perror("fopen() failed");
    exit(1);
  }
  char buffer[1024];
  int i = 0;
  printf("\n/proc/self/maps\n");
  while (!feof(fp)) {
    if (fgets(buffer, sizeof(buffer), fp) != NULL)
      printf("%02d>\t%s", ++i, buffer);
  }
  fclose(fp);
#endif
}

int main(void) {

  char *ptr1 = (char *)malloc(10 * sizeof(char));
  printf("\nAddress of ptr1: %p\n", (void *)&ptr1);
  printf("Memory allocated by malloc at %p: ", (void *)ptr1);
  for (int i = 0; i < 10; i++) {
    printf("0x%02x ", (unsigned char)ptr1[i]);
  }
  printf("\n");

  char *ptr2 = (char *)malloc(10 * sizeof(char));
  printf("Address of ptr2: %p\n", (void *)&ptr2);
  printf("Memory allocated by malloc at %p: ", (void *)ptr2);
  for (int i = 0; i < 10; i++) {
    printf("0x%02x ", (unsigned char)ptr2[i]);
  }
  printf("\n");

  print_mem_map();

  free(ptr1);
  free(ptr2);

  return 0;
}
