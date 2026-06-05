#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <NovelRT/Ecs/Scripting/DecisionTreeStepManager.hpp>

#include <NovelRT/Scripting/ScriptManager.hpp>

#include <unordered_map>

namespace NovelRT::Ecs::Scripting
{
    class DecisionTreeStepSystem : public NovelRT::Ecs::IEcsSystem
    {
        DecisionTreeStepManager _stepManager;

    public:
        DecisionTreeStepSystem(DecisionTreeStepManager);

        ~DecisionTreeStepSystem() override = default;

        void Update(Timing::Timestamp, Catalogue) override;
    };
}
