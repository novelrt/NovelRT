#include <stdio.h>
#include "../src/NovelRT.C/GeoVector2F.h"

int main(int argc, char **argv) {
  struct GeoVector2F gv = { 5.0f, 5.0f };
  printf("Hello from C!\nGeoVector2 of 5.0f, 5.0f\n X = %1f, Y = %1f\nLength is %3f", GeoVector2F_getX(gv), GeoVector2F_getY(gv), GeoVector2F_getLength(gv));

  (int)argc;
  (void*)argv;
  return 0;
}
