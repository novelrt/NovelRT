#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

namespace NovelRT::Ecs::Scripting::Graphics
{
    class PoseToSpriteTranslationSystem : public NovelRT::Ecs::IEcsSystem
    {
        void Update(Timing::Timestamp, Catalogue);
    };
}
