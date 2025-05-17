// File name: ExtremeC_examples1_05.c
// Description: Variadic macros to generate a generic error message making sure
// a command line arguments and options are properly formated.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "3.0.2"
#define LOG_ERROR(format, ...) fprintf(stderr, format, __VA_ARGS__);

int main(int argc, char *argv[]) {

  if (argc < 3) {
    LOG_ERROR("Invalid number of arguments for version %s\n", VERSION)
  }

  if (argc > 2 && strcmp(argv[2], "--norm") != 0) {
    LOG_ERROR("'%s' is invalid parameter at index %d for version %s\n", argv[2],
              2, VERSION)
  }

  return EXIT_SUCCESS;
}
