// File name: ExtremeC_examples1_08.c
// Description: Header guard statement. A conditional compilation trick to
// prevent redundant expansion of header files.

#ifndef EXAMPLE_1_8_H

  #define EXAMPLE_1_8_H
  #include <stdio.h>
  
  void say_hello(void) { printf("Hello!\n"); };
  int read_age();

#endif
