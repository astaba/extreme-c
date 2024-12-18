// File name: ExtremeC_exampels_chapter1_4.c
// Description: Example 1.4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD(X)                                                                 \
  char X##_cmd[256];                                                           \
  strcpy(X##_cmd, #X);

int main(void) {
  CMD(copy);
  CMD(paste)
  CMD(cut)

  char cmd[256];
  scanf("%s", cmd);

  if (strcmp(cmd, copy_cmd) == 0)
    printf("%s successful\n", copy_cmd);
  if (strcmp(cmd, paste_cmd) == 0)
    printf("%s successful\n", paste_cmd);
  if (strcmp(cmd, cut_cmd) == 0)
    printf("%s successful\n", cut_cmd);

  return EXIT_SUCCESS;
}
