// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_GRAPHICS_H
#define NOVELRT_PERSISTENCE_GRAPHICS_H

#include "../Persistence.h"

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

// Persistence.Graphics Dependencies
#include <uuid.h>

namespace NovelRT::Persistence::Graphics
{
    class RenderingComponentPersistenceRule;
}

// clang-format off
#include "RenderingComponentPersistenceRule.h"
// clang-format on

#endif // NOVELRT_PERSISTENCE_GRAPHICS_H
