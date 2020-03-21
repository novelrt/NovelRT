#include "GeoVector2F.h"
#include "NovelRT.h"

GeoVector2F GeoVector2_create(float x, float y) {
  struct GeoVector2F gv = { x,y };
  return gv;
}

float GeoVector2F_getX(GeoVector2F_t gv) {
  return gv.x;
}

float GeoVector2F_getY(GeoVector2F_t gv) {
  return gv.y;
}

void GeoVector2F_setX(GeoVector2F_t gv, float value) {
  gv.x = value;
}

void GeoVector2F_setY(GeoVector2F_t gv, float value) {
  gv.y = value;
}

float GeoVector2F_getLength(GeoVector2F_t gv) {
  NovelRT::Maths::GeoVector2<float> geo = NovelRT::Maths::GeoVector2<float>(gv.x, gv.y);

  return geo.getLength();
}
