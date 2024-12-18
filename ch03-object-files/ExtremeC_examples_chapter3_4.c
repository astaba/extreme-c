// File name: ExtremeC_examples_chapter3_4.c
// Description: Load the shared object file using dlopen
// NOTE: Why dlclose Is Important:
//  Resource Management: It releases resources allocated for the shared library
//  by the operating system.
//  Avoid Memory Leaks: Without dlclose, the memory used
//  for the shared library remains occupied until the program terminates.

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "ExtremeC_examples_chapter3_2_geometry.h"

int main(void) {

  void *handle = dlopen("./opt/geometry/libgeometry.so", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  polar_pos_3d_t (*func_ptr)(cartesian_pos_3d_t *);
  func_ptr = dlsym(handle, "convert_to_3d_polar_pos");
  if (!func_ptr) {
    fprintf(stderr, "%s\n", dlerror());
    dlclose(handle); // Close the library before exiting
    exit(EXIT_FAILURE);
  }

  cartesian_pos_3d_t cartesian_pos;
  cartesian_pos.x = 100;
  cartesian_pos.y = 50;
  cartesian_pos.z = 300;

  polar_pos_3d_t polar_pos = func_ptr(&cartesian_pos);

  printf("Polar position:\n\t%6s: %f\n\t%6s: %f (deg)\n\t%6s: %f (deg)\n",
         "Length", polar_pos.length, "Theat", polar_pos.theta, "Phi",
         polar_pos.phi);

  // Close the library handle
  dlclose(handle);
  return EXIT_SUCCESS;
}
