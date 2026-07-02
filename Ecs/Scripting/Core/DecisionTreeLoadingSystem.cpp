// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Scripting/Components/DecisionTreeLoadRequest.hpp>
#include <NovelRT/Ecs/Scripting/Components/LoadedDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/DecisionTreeLoadingSystem.hpp>

#include <NovelRT/Scripting/DecisionTree.hpp>

#include <algorithm>

struct NovelRT::Ecs::Scripting::DecisionTreeLoadingSystem::LoadRequest
{
    NovelRT::Ecs::EntityId entity;
    uuids::uuid assetId;
};

struct NovelRT::Ecs::Scripting::DecisionTreeLoadingSystem::LoadResult
{
    NovelRT::Ecs::EntityId entity;
    uuids::uuid assetId;
    NovelRT::Scripting::DecisionTree* decisionTree;
};

auto NovelRT::Ecs::Scripting::DecisionTreeLoadingSystem::GetLoadRequests(
    ComponentView<Components::DecisionTreeLoadRequest>& requests) -> std::vector<LoadRequest>
{
    std::vector<LoadRequest> result{};

    for (const auto& [entity, component] : requests)
    {
        result.emplace_back(entity, component.assetId);
    }

    return result;
}

NovelRT::Ecs::Scripting::DecisionTreeLoadingSystem::DecisionTreeLoadingSystem(
    const std::shared_ptr<NovelRT::Scripting::ScriptManager>& manager,
    const std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader>& resourceLoader)
    : _scriptManager{manager}, _resourceLoader{resourceLoader}
{
}

void NovelRT::Ecs::Scripting::DecisionTreeLoadingSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    auto loadRequests = catalogue.GetComponentView<Components::DecisionTreeLoadRequest>();
    if (loadRequests.begin() == loadRequests.end())
    {
        return;
    }

    auto requests = GetLoadRequests(loadRequests);

    catalogue.ScheduleWithCompletion(
        [requests = std::move(requests), loader = _resourceLoader, manager = _scriptManager, &mutex = _loadingMutex]()
        {
            std::scoped_lock lock(mutex);

            std::vector<std::pair<EntityId, NovelRT::ResourceManagement::ScriptMetadata>> sources(requests.size());
            std::transform(requests.begin(), requests.end(), sources.begin(), [&loader](const auto& request)
                           { return std::make_pair(request.entity, loader->LoadScript(request.assetId)); });

            std::vector<LoadResult> results(requests.size());
            std::transform(sources.begin(), sources.end(), results.begin(), [&manager](const auto& pair)
                           { return LoadResult{pair.first, pair.second.databaseHandle, manager->LoadDecisionTree(pair.second.scriptCode).release()}; });

            return results;
        },
        [](Timing::Timestamp /* delta */, Catalogue catalogue, std::vector<LoadResult> results)
        {
            auto loadedTrees = catalogue.GetComponentView<Components::LoadedDecisionTree>();
            std::for_each(results.begin(), results.end(),
                          [&loadedTrees](auto& result)
                          {
                              loadedTrees.PushComponentUpdateInstruction(
                                  result.entity,
                                  Components::LoadedDecisionTree{
                                      result.assetId,
                                      new std::shared_ptr<NovelRT::Scripting::DecisionTree>(result.decisionTree)});
                          });
        });
}
