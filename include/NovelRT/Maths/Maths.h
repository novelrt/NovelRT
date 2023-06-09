// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_MATHS_H
#define NOVELRT_MATHS_H

// Maths dependencies
#include "../Core/Core.h"
#include <array>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <memory>
#include <vector>

/**
 * @brief Contains features in assisting with mathematical operations, such as structures for vector and matrix maths.
 */
namespace NovelRT::Maths
{
    class GeoBounds;
    class GeoMatrix4x4F;
    class GeoVector2F;
    class GeoVector3F;
    class GeoVector4F;
    class QuadTree;
    class QuadTreePoint;
}

// clang-format off

#include "Utilities.h"
#include "GeoVector2F.h"
#include "GeoBounds.h"
#include "GeoVector3F.h"
#include "GeoVector4F.h"
#include "GeoMatrix4x4F.h"
#include "QuadTreePoint.h"
#include "QuadTree.h"

// clang-format on

#endif // NOVELRT_MATHS_H
