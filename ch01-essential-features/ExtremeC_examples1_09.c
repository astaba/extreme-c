// File name: ExtremeC_examples1_09.c
// Description: Pointers.

int main(int argc, char** argv) {
  int var = 100;
  int* ptr = 0;
  ptr = &var;
  *ptr = 200;
  return 0;
}
