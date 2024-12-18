// File name: ExtremeC_examples_chapter2_1.h
// Description: Contains the declaration needed for the 'avg' function

// 'header guard' statement technique
#ifndef EXTREMEC_EXAMPLES_CHAPTER_2_1_H
#define EXTREMEC_EXAMPLES_CHAPTER_2_1_H

// enum declaration and definition cannot be separated
typedef enum {
  NONE,
  NORMAL,
  SQUARED
} average_type_t;

// 'forward declaration' of the avg function
double avg(int*, int, average_type_t);

#endif
