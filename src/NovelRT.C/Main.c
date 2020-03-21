#include <stdio.h>
#include "GeoVector2_C.h"

int main(int argc, char **argv) {
  GeoVector2_t* gv = GeoVector2_create(0.0f, 0.0f);
  printf("GeoVector2 of 0.0, 0.0\n X = %f\nHello from C!", GeoVector2_getX(gv));

  (int)argc;
  (void*)argv;
  return 0;
}
