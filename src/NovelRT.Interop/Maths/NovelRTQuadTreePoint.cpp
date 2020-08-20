// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/Maths/NovelRTQuadTreePoint.h"
#include "NovelRT.h"
#include <list>
#include <algorithm>

std::list<std::shared_ptr<NovelRT::Maths::QuadTreePoint>> _pointCollection; //TODO: Why a list? - Ruby

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  NovelRTQuadTreePoint NovelRT_QuadTreePoint_create(NovelRTGeoVector2F position) {
    _pointCollection.push_back(std::make_shared<Maths::QuadTreePoint>(reinterpret_cast<Maths::GeoVector2<float>&>(position)));
    return reinterpret_cast<NovelRTQuadTreePoint>(_pointCollection.back().get());
  }

  NovelRTQuadTreePoint NovelRT_QuadTreePoint_createFromFloat(float x, float y) {
    _pointCollection.push_back(std::make_shared<Maths::QuadTreePoint>(Maths::GeoVector2<float>(x, y)));
    return reinterpret_cast<NovelRTQuadTreePoint>(_pointCollection.back().get());
  }

  NovelRTResult NovelRT_QuadTreePoint_getPosition(const NovelRTQuadTreePoint point, NovelRTGeoVector2F* outputPosition, const char** errorMessage) {
    if(point == nullptr || outputPosition == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& pos = reinterpret_cast<const std::shared_ptr<Maths::QuadTreePoint>&>(point)->getPosition();
    NovelRTGeoVector2F returnValue = reinterpret_cast<const NovelRTGeoVector2F&>(pos);
    *outputPosition = returnValue;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_QuadTreePoint_delete(NovelRTQuadTreePoint point, const char** errorMessage) {
    if(point == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    auto ptr = reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this();

    if(std::find(_pointCollection.begin(), _pointCollection.end(), ptr) == _pointCollection.end()) { //TODO: This may prove to be a bottleneck later
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    _pointCollection.remove(reinterpret_cast<Maths::QuadTreePoint*>(point)->shared_from_this());
    return NOVELRT_SUCCESS;
  }



#ifdef __cplusplus

}
#endif
