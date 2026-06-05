#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <NovelRT/Ecs/Scripting/DecisionTreeStepSystem.hpp>

#include <memory>

namespace NovelRT::Ecs::Scripting
{
    class SpokenLineStepSystem final : public NovelRT::Ecs::Scripting::DecisionTreeStepSystem
    {
    public:
        SpokenLineStepSystem(DecisionTreeStateManager&, SystemScheduler&);
        ~SpokenLineStepSystem() override = default;

        void Update(Timing::Timestamp delta, Catalogue catalogue) override;
    };
}
