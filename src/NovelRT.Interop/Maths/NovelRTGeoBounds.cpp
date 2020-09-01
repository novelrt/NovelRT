// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include "NovelRT.Interop/Maths/NovelRTGeoBounds.h"


#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  NovelRTGeoBounds NovelRT_GeoBounds_zero() {
    return NovelRTGeoBounds{ NovelRT_GeoVector2F_zero(),  NovelRT_GeoVector2F_zero(), 0.0f };
  }

  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInLocalSpace(NovelRTGeoBounds bounds, int index) {
    Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2F corner = cBounds.getCornerInLocalSpace(index);
    return reinterpret_cast<NovelRTGeoVector2F&>(corner);
  }

  NovelRTGeoVector2F NovelRT_GeoBounds_getCornerInWorldSpace(NovelRTGeoBounds bounds, int index) {
    Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2F corner = cBounds.getCornerInWorldSpace(index);
    return reinterpret_cast<NovelRTGeoVector2F&>(corner);
  }

  NovelRTBool NovelRT_GeoBounds_pointIsWithinBounds(NovelRTGeoBounds bounds, NovelRTGeoVector2F point) {
    Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2F cPoint = *reinterpret_cast<Maths::GeoVector2F*>(&point);
    if (cBounds.pointIsWithinBounds(cPoint)) {
      return NOVELRT_TRUE;
    }
    return NOVELRT_FALSE;
  }

  NovelRTGeoVector2F NovelRT_GeoBounds_getExtents(NovelRTGeoBounds bounds) {
    const Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
    Maths::GeoVector2F extents = cBounds.getExtents(); 
    return reinterpret_cast<NovelRTGeoVector2F&>(extents);
  }

  NovelRTResult NovelRT_GeoBounds_intersectsWith(NovelRTGeoBounds first, NovelRTGeoBounds other, NovelRTBool* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      return NOVELRT_FAILURE;
    }

    try {
      Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&first);
      Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&other);
      if (cFirst.intersectsWith(cOther)) {
        *outputResult = NOVELRT_TRUE;
      } else {
        *outputResult = NOVELRT_FALSE;
      }
      
      return NOVELRT_SUCCESS;

    } catch (const std::exception& ex) {
      (void)ex;
      if(errorMessage != nullptr) {
        *errorMessage = "TODO: Figure out how to push exception message proper.";
      }

      return NOVELRT_FAILURE;
    }
  }

  NovelRTBool NovelRT_GeoBounds_equal(NovelRTGeoBounds lhs, NovelRTGeoBounds rhs) {
    Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&lhs);
    Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&rhs);

    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }
    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoBounds_notEqual(NovelRTGeoBounds lhs, NovelRTGeoBounds rhs) {
    Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&lhs);
    Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&rhs);

    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }
    return NOVELRT_FALSE;
  }

}

