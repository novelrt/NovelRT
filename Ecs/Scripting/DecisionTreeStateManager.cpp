// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Scripting/DecisionTreeStateManager.hpp>

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>

#include <algorithm>

void NovelRT::Ecs::Scripting::DecisionTreeStateManager::RegisterStateHandler(StateHandler handler)
{
    _stateHandlers.emplace_back(handler);
}

void NovelRT::Ecs::Scripting::DecisionTreeStateManager::HandleStateChange(
    NovelRT::Ecs::Catalogue& catalogue,
    EntityId entity,
    std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>& state)
{
    for (const auto& handler : _stateHandlers)
    {
        if (handler(state, catalogue, entity))
        {
            break;
        }
    }
}
