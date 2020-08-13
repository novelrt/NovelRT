// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/QuadTreePoint_t.h"
#include "NovelRT.h"
#include <list>

std::list<std::shared_ptr<NovelRT::Maths::QuadTreePoint>> _pointCollection; //TODO: Why a list? - Ruby

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  QuadTreePoint_t QuadTreePoint_create(NovelRTGeoVector2F& position) {
    _pointCollection.push_back(std::make_shared<Maths::QuadTreePoint>(reinterpret_cast<Maths::GeoVector2<float>&>(position)));
    return reinterpret_cast<QuadTreePoint_t>(_pointCollection.back().get());
  }

  QuadTreePoint_t QuadTreePoint_createFromFloat(float x, float y) {
    _pointCollection.push_back(std::make_shared<Maths::QuadTreePoint>(Maths::GeoVector2<float>(x, y)));
    return reinterpret_cast<QuadTreePoint_t>(_pointCollection.back().get());
  }

  NovelRTGeoVector2F QuadTreePoint_getPosition(QuadTreePoint_t point) {
    Maths::GeoVector2<float>* pos = new Maths::GeoVector2<float>();
    *pos = reinterpret_cast<std::shared_ptr<Maths::QuadTreePoint>&>(point)->getPosition();
    return reinterpret_cast<const NovelRTGeoVector2F&>(*pos);
  }

  void QuadTreePoint_delete(QuadTreePoint_t point) {
    _pointCollection.remove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this());
  }



#ifdef __cplusplus

}
#endif
