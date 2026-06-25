#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <NovelRT/ResourceManagement/ResourceLoader.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>

#include <memory>
#include <unordered_map>

namespace NovelRT::Ecs::Scripting::Graphics
{
    class PoseToSpriteTranslationSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        struct CharacterInfo
        {
            std::unordered_map<std::string, uuids::uuid> knownPoses;
            uuids::uuid activePose;
            NovelRT::Maths::GeoVector2F position{0, 0};
            NovelRT::Maths::GeoVector2F scale{1, 1};
            NovelRT::Ecs::EntityId sprite;
        };

        struct TreeInfo
        {
            std::unordered_map<std::string, CharacterInfo> knownCharacters;
        };

        std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader> _resourceLoader;

        std::unordered_map<EntityId, TreeInfo> _activeTrees;

        void CleanupInactiveTrees(Catalogue& catalogue);
        void IdentifyNewTrees(Catalogue& catalogue);

        void UpdateCharacterInformation(Catalogue& catalogue);

        void ApplySpriteUpdates(Catalogue& catalogue);

    public:
        PoseToSpriteTranslationSystem(
            const std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader>& resourceLoader);

        void Update(Timing::Timestamp, Catalogue);
    };
}
