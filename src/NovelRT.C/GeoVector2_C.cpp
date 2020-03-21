#include "GeoVector2_C.h"
#include "NovelRT.h"

struct GeoVector2 {
  void *obj;
};

GeoVector2_t *GeoVector2_create(float x, float y) {
  GeoVector2_t *gv;
  GeoVector2 *obj;

#ifdef WIN32
  gv = (decltype(gv))malloc(sizeof(*gv));
#else
  gv = (typeof(gv))malloc(sizeof(*gv));
#endif
  
  obj = reinterpret_cast<GeoVector2_t*>(new NovelRT::Maths::GeoVector2<float>(x,y));
  gv->obj = obj;
  return gv;
}

float GeoVector2_getX(GeoVector2_t *gv) {
  NovelRT::Maths::GeoVector2<float>* obj;

  if (gv == NULL)
    return -1;

  obj = reinterpret_cast<NovelRT::Maths::GeoVector2<float>*>(gv->obj);
  return obj->getX();
}

float GeoVector2_getY(GeoVector2_t* gv) {
  NovelRT::Maths::GeoVector2<float>* obj;

  if (gv == NULL)
    return -1;

  obj = reinterpret_cast<NovelRT::Maths::GeoVector2<float>*>(gv->obj);
  return obj->getY();
}
