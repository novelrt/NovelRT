// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRTMATHSGEOBOUNDSH
#define NOVELRTMATHSGEOBOUNDSH

#ifndef NOVELRTH
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

#include "BaseGeoBounds.h"

namespace NovelRT::Maths {
  class GeoBounds : public NovelRTGeoBounds {
  public:
    GeoBounds(const GeoVector2F& position, const GeoVector2F& size, float rotation);
    bool pointIsWithinBounds(const GeoVector2F& point) const;
    bool intersectsWith(const GeoBounds& otherBounds) const;
    GeoVector2F getCornerInLocalSpace(int index) const;
    GeoVector2F getCornerInWorldSpace(int index) const;
    GeoVector2F getExtents() const;

    inline bool operator==(const GeoBounds& other) const {
      return position == other.position
          && size == other.size
          && rotation == other.rotation;
    }

    inline bool operator!=(const GeoBounds& other) const {
      return position != other.position
        || size != other.size
        || rotation != other.rotation;
    }
  };
}

#endif //NOVELRTMATHSGEOBOUNDSH
