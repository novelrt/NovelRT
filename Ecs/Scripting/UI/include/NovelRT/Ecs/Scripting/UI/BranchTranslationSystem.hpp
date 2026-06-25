#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <NovelRT/ResourceManagement/ResourceLoader.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>

#include <memory>
#include <unordered_map>

namespace NovelRT::Ecs::Scripting::UI
{
    class BranchTranslationSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        struct TreeInfo
        {
            EntityId messageContainer;
            EntityId message;

            EntityId choiceContainer;
            std::vector<EntityId> choices;

            std::string prompt;
            std::vector<std::string> choiceLabels;
        };

        std::string _choicesText = "Choices";
        std::string _promptText = "Prompt";

        std::unordered_map<EntityId, TreeInfo> _activeTrees;

        void CleanupInactiveTrees(Catalogue& catalogue);
        void IdentifyNewTrees(Catalogue& catalogue);

        void UpdateContainers(Catalogue& catalogue);

    public:
        BranchTranslationSystem();

        void Update(Timing::Timestamp, Catalogue);
    };
}
