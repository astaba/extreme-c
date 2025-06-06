// File name: ExtremeC_examples_chapter2_1_main.c
// Description: Contains the 'main' function

#include <stdio.h>
#include "ExtremeC_examples_chapter2_1.h"

#define LENGTH 5

int main(int argc, char** argv) {
  // Array declaration
  int array[LENGTH];

  // Filling the array
  array[0] = 10;
  array[1] = 3;
  array[2] = 5;
  array[3] = -8;
  array[4] = 9;

  // Calculating the averages using the 'avg' function
  double average = avg(array, LENGTH, NORMAL);
  printf("The average: %g\n", average);

  average = avg(array, 5, SQUARED);
  printf("The squared average: %g\n", average);

  return 0;
}
