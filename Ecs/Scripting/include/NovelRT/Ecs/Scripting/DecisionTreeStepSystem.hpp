#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>
#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <memory>

namespace NovelRT::Scripting
{
    class DecisionTreeStatus;
}

namespace NovelRT::Ecs::Scripting
{
    class DecisionTreeStateManager;

    class DecisionTreeStepSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        DecisionTreeStateManager& _stepManager;

    protected:
        DecisionTreeStepSystem(DecisionTreeStateManager&);

        void Continue(Catalogue& catalogue, EntityId entity, std::unique_ptr<NovelRT::Scripting::DecisionTreeStatus>&& status);

    public:
        virtual ~DecisionTreeStepSystem() override = default;
    };
}
