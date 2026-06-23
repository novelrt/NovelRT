// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Catalogue.hpp>
#include <NovelRT/Ecs/ComponentBuffer.hpp>
#include <NovelRT/Ecs/ComponentView.hpp>
#include <NovelRT/Ecs/SparseSet.hpp>

#include <NovelRT/Ecs/Components/TransformComponent.hpp>
#include <NovelRT/Ecs/Graphics/Components/Sprite.hpp>
#include <NovelRT/Ecs/Scripting/Components/ActiveDecisionTree.hpp>
#include <NovelRT/Ecs/Scripting/Components/Pose.hpp>
#include <NovelRT/Ecs/Scripting/Components/SpokenLine.hpp>

#include <NovelRT/Ecs/Scripting/Graphics/PoseToSpriteTranslationSystem.hpp>

#include <algorithm>

void NovelRT::Ecs::Scripting::Graphics::PoseToSpriteTranslationSystem::CleanupInactiveTrees(Catalogue& catalogue)
{
    auto trees = catalogue.GetComponentView<Components::ActiveDecisionTree>();

    for (auto it = _activeTrees.begin(), end = _activeTrees.end(); it != end;)
    {
        if (trees.HasComponent(it->first))
        {
            ++it;
            continue;
        }

        for (const auto& [_, character] : it->second.knownCharacters)
        {
            catalogue.DeleteEntity(character.sprite);
        }

        it = _activeTrees.erase(it);
    }
}

void NovelRT::Ecs::Scripting::Graphics::PoseToSpriteTranslationSystem::IdentifyNewTrees(Catalogue& catalogue)
{
    auto trees = catalogue.GetComponentView<Components::ActiveDecisionTree>();

    for (auto [entity, _] : trees)
    {
        auto it = _activeTrees.find(entity);
        if (it != _activeTrees.end())
        {
            continue;
        }

        _activeTrees.emplace_hint(it, entity, TreeInfo{ });
    }
}

void NovelRT::Ecs::Scripting::Graphics::PoseToSpriteTranslationSystem::UpdateCharacterInformation(Catalogue& catalogue)
{
    auto [spokenLines, poses] = catalogue.GetComponentViews<Components::SpokenLine, Components::Pose>();

    for (auto& [entity, info] : _activeTrees)
    {
        if (!spokenLines.HasComponent(entity) || !poses.HasComponent(entity))
        {
            continue;
        }

        auto spokenLine = spokenLines.GetComponent(entity);
        auto pose = poses.GetComponent(entity);
        auto characterIt = info.knownCharacters.find(*spokenLine.speaker);
        if (characterIt == info.knownCharacters.end())
        {
            CharacterInfo characterInfo{ .knownPoses = {}, .activePose = {}, .sprite = catalogue.CreateEntity() };

            auto sprite = _resourceLoader->TryGetAssetIdBasedOnFilePath(*pose.sprite);
            if (sprite.has_value())
            {
                characterInfo.knownPoses[*pose.name] = sprite.value();
            }

            characterIt = info.knownCharacters.emplace_hint(characterIt, *spokenLine.speaker, characterInfo);
        }

        auto& characterInfo = characterIt->second;
        auto poseIt = characterInfo.knownPoses.find(*pose.name);
        if (poseIt == characterInfo.knownPoses.end())
        {
            auto sprite = _resourceLoader->TryGetAssetIdBasedOnFilePath(*pose.sprite);
            if (!sprite.has_value())
            {
                continue;
            }

            poseIt = characterInfo.knownPoses.emplace_hint(poseIt, *pose.name, sprite.value());
        }

        characterInfo.activePose = poseIt->second;
        characterInfo.position = pose.position;
        characterInfo.scale = pose.scale;
    }
}

void NovelRT::Ecs::Scripting::Graphics::PoseToSpriteTranslationSystem::ApplySpriteUpdates(Catalogue& catalogue)
{
    auto [sprites, transforms] = catalogue.GetComponentViews<NovelRT::Ecs::Graphics::Components::Sprite, NovelRT::Ecs::Components::TransformComponent>();

    for (const auto& [entity, info] : _activeTrees)
    {
        for (const auto& [_, character] : info.knownCharacters)
        {
            sprites.PushComponentUpdateInstruction(character.sprite, NovelRT::Ecs::Graphics::Components::Sprite{
                .assetId = character.activePose
            });

            transforms.PushComponentUpdateInstruction(character.sprite, NovelRT::Ecs::Components::TransformComponent{
                .position = character.position,
                .scale = character.scale
            });
        }
    }
}

NovelRT::Ecs::Scripting::Graphics::PoseToSpriteTranslationSystem::PoseToSpriteTranslationSystem(
    const std::shared_ptr<NovelRT::ResourceManagement::ResourceLoader>& resourceLoader)
: _resourceLoader{resourceLoader}
{
}

void NovelRT::Ecs::Scripting::Graphics::PoseToSpriteTranslationSystem::Update(Timing::Timestamp /* delta */, Catalogue catalogue)
{
    CleanupInactiveTrees(catalogue);
    IdentifyNewTrees(catalogue);
    UpdateCharacterInformation(catalogue);
    ApplySpriteUpdates(catalogue);
}

