/* ch02-compilation-and-linking/ExtremeC_examples_chapter2_x.c */
// Description: Text file to show that preprocessors like cpp
// don't know C syntax for error checking but are only concerned with text
// substitution. Preprocess it and check the translation unit.

#include <stdio.h>
#define file 1000

This is just a simple text file but ending with the .c extension!
This is not a C file for sure.
But we can preprocess it!
