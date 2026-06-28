#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <NovelRT/ResourceManagement/ResourceLoader.hpp>

#include <NovelRT/Scripting/ScriptManager.hpp>

#include <tbb/mutex.h>

namespace NovelRT::Ecs::Scripting::Components
{
    struct DecisionTreeLoadRequest;
}

namespace NovelRT::Ecs::Scripting
{
    class DecisionTreeLoadingSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Scripting::ScriptManager> _scriptManager;
        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> _resourceLoader;

        tbb::mutex _loadingMutex;

        struct LoadRequest;
        struct LoadResult;

        std::vector<LoadRequest> GetLoadRequests(ComponentView<Components::DecisionTreeLoadRequest>& requests);

    public:
        DecisionTreeLoadingSystem(const std::shared_ptr<NovelRT::Scripting::ScriptManager>& manager,
                                  const std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader>& resourceLoader);

        void Update(Timing::Timestamp, Catalogue);
    };
}
