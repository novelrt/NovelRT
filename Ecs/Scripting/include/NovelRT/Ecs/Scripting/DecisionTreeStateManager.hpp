#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>

#include <NovelRT/Utilities/Atom.hpp>

#include <functional>
#include <memory>
#include <vector>

namespace NovelRT::Scripting
{
    class DecisionTreeStatus;
}

namespace NovelRT::Ecs
{
    class Catalogue;
}

namespace NovelRT::Ecs::Scripting
{
    class EcsScriptingBuilder;

    class DecisionTreeStateManager
    {
    public:
        // Handler for binding a state to ECS
        using StateHandler = std::function<bool(std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&, NovelRT::Ecs::Catalogue&, EntityId)>;

    private:
        std::vector<StateHandler> _stateHandlers;

        explicit DecisionTreeStateManager() = default;

        friend EcsScriptingBuilder;

    public:
        DecisionTreeStateManager(const DecisionTreeStateManager& other) = default;
        DecisionTreeStateManager& operator=(const DecisionTreeStateManager& other) = default;
        DecisionTreeStateManager(DecisionTreeStateManager&& other) = default;
        DecisionTreeStateManager& operator=(DecisionTreeStateManager&& other) = default;
        ~DecisionTreeStateManager() = default;

        void RegisterStateHandler(StateHandler handler);

        void HandleStateChange(NovelRT::Ecs::Catalogue& catalogue, EntityId entity, std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>& state);
    };
}
