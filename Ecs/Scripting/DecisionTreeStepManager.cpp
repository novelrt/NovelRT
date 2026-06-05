// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Scripting/DecisionTreeStepManager.hpp>

NovelRT::Ecs::Scripting::DecisionTreeStepManager::DecisionTreeStepManager() = default;

auto NovelRT::Ecs::Scripting::DecisionTreeStepManager::RegisterStepHandler(std::function<void(NovelRT::Ecs::Catalogue&,EntityId,std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&)> handler) -> DecisionTreeStepKind
{
    static AtomFactory& stepHandlerIdFactory = AtomFactoryDatabase::GetFactory("NovelRT::Ecs::Scripting::DecisionTreeStepKind");

    auto [it, inserted] = _registeredStepHandlers.emplace(std::make_tuple(handler, stepHandlerIdFactory.GetNext()));

    if (inserted)
    {
        _reverseStepHandlerMapping[std::get<DecisionTreeStepKind>(*it)] = handler;
    }

    return std::get<DecisionTreeStepKind>(*it);
}

const std::function<void(NovelRT::Ecs::Catalogue&,NovelRT::Ecs::EntityId,std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&)>& NovelRT::Ecs::Scripting::DecisionTreeStepManager::GetStepHandler(DecisionTreeStepKind id) const
{
    return _reverseStepHandlerMapping.at(id);
}
