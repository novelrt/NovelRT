#include "NovelC/GeoVector2F.h"
#include "NovelC/GeoBounds.h"
#include "NovelRT.h"


extern "C" {
  GeoBounds_t GeoBounds_create(const GeoVector2F_t& position, const GeoVector2F_t& size, float rotation) {
    GeoBounds_t bounds = { position, rotation, size };
    return bounds;
  }

  GeoVector2F_t GeoBounds_getCornerInLocalSpace(const GeoBounds_t& bounds, int index) {
    //reinterpret_cast fails here - ISO C doesn't allow conversion to/from structs
    NovelRT::Maths::GeoVector2<float> pos = NovelRT::Maths::GeoVector2<float>(bounds._position.x, bounds._position.y);
    NovelRT::Maths::GeoVector2<float> sz = NovelRT::Maths::GeoVector2<float>(bounds._size.x, bounds._size.y);
    NovelRT::Maths::GeoBounds boundary = NovelRT::Maths::GeoBounds(pos, sz, bounds._rotation);
    NovelRT::Maths::GeoVector2<float> corner = boundary.getCornerInLocalSpace(index);
    return { corner.getX(), corner.getY() };
  }

  GeoVector2F_t GeoBounds_getCornerInWorldSpace(GeoBounds_t& bounds, int index) {
    return GeoVector2F_addVector(bounds._position, GeoBounds_getCornerInLocalSpace(bounds, index));
  }

  bool GeoBounds_pointIsWithinBounds(const GeoBounds_t& bounds, const GeoVector2F_t& point) {
    NovelRT::Maths::GeoVector2<float> pos = NovelRT::Maths::GeoVector2<float>(bounds._position.x, bounds._position.y);
    NovelRT::Maths::GeoVector2<float> sz = NovelRT::Maths::GeoVector2<float>(bounds._size.x, bounds._size.y);
    NovelRT::Maths::GeoBounds boundary = NovelRT::Maths::GeoBounds(pos, sz, bounds._rotation);
    return boundary.pointIsWithinBounds(NovelRT::Maths::GeoVector2<float>(point.x, point.y));
  }

  const GeoVector2F_t& GeoBounds_position(const GeoBounds_t& bounds) {
    return bounds._position;
  }

  const GeoVector2F& GeoBounds_size(const GeoBounds_t& bounds) {
    return bounds._size;
  }

  const float& GeoBounds_rotation(const GeoBounds_t& bounds) {
    return bounds._rotation;
  }

  GeoVector2F_t GeoBounds_getExtents(GeoBounds_t& bounds) {
    return GeoVector2F_divideFloat(bounds._size, 2.0f);
  }

  bool GeoBounds_intersectsWith(const GeoBounds_t& firstBounds, const GeoBounds_t& otherBounds) {
    NovelRT::Maths::GeoBounds one = NovelRT::Maths::GeoBounds(NovelRT::Maths::GeoVector2<float>(firstBounds._position.x, firstBounds._position.y),
      NovelRT::Maths::GeoVector2<float>(firstBounds._size.x, firstBounds._size.y), firstBounds._rotation);
    NovelRT::Maths::GeoBounds two = NovelRT::Maths::GeoBounds(NovelRT::Maths::GeoVector2<float>(otherBounds._position.x, otherBounds._position.y),
      NovelRT::Maths::GeoVector2<float>(otherBounds._size.x, otherBounds._size.y), otherBounds._rotation);

    return one.intersectsWith(two);
  }
}
