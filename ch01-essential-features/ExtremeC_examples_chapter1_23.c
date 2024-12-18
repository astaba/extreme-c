// File name: ExtremeC_exampels_chapter1_23.c
// Description: Example 1.23

typedef struct point {
  int x;
  int y;
} point_t;

typedef struct circle {
  point_t center;
  int radius;
} circle_t;

typedef struct line {
  point_t start;
  point_t end;
} line_t;
