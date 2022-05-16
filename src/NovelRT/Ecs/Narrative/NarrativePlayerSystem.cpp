// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include "NovelRT/Ecs/Narrative/NarrativePlayerSystem.h"

namespace NovelRT::Ecs::Narrative
{
    void NarrativePlayerSystem::Update(Timing::Timestamp delta, Catalogue catalogue)
    {
        auto playerStateBuffer = catalogue.GetComponentView<NarrativePlayerStateComponent>();

        for (auto [entity, playerStateComponent] : playerStateBuffer)
        {
            switch (playerStateComponent.currentState)
            {
                // Do nothing. - Matt
                case NarrativePlayerState::Idle:
                    break;
                // Set state to playing and execute the section accordingly. You should update the instruction call here to represent correct state. - Matt
                case NarrativePlayerState::RequestPlay:
                    playerStateBuffer.PushComponentUpdateInstruction(entity, NarrativePlayerStateComponent{NarrativePlayerState::Playing, playerStateComponent.sectionId, playerStateComponent.characterId});
                    break;
                // Ensure that the player state component gets an update on accurate information e.g. which character is talking and which section is running. - Matt
                case NarrativePlayerState::Playing:
                    break;
                // Set state to Idle and stop executing. - Matt
                case NarrativePlayerState::RequestStop:
                    break;
                // Destroy the narrative player state component and then do whatever you see fit internally based on that. - Matt
                case NarrativePlayerState::RequestDestroy:
                    playerStateBuffer.RemoveComponent(entity);
                    break;
            }
        }
    }

    void NarrativePlayerSystem::RegisterInformationToCharacter(const std::string& name)
    {
    }
}