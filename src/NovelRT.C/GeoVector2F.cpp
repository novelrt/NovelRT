#include "GeoVector2F.h"
#include "NovelRT.h"

GeoVector2F GeoVector2_create(float x, float y) {
  struct GeoVector2F gv = { x,y };
  return gv;
}

float GeoVector2F_getX(GeoVector2_t* gv) {
  return gv->x;
}

float GeoVector2F_getY(GeoVector2_t* gv) {
  return gv->y;
}

void GeoVector2F_setX(GeoVector2_t* gv, float value) {
  gv->x = value;
}

void GeoVector2F_setY(GeoVector2_t* gv, float value) {
  gv->y = value;
}

