// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_NARRATIVEPLAYERSYSTEM_H
#define NOVELRT_NARRATIVEPLAYERSYSTEM_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    // This type should be as immutable as possible. Any methods that mutate the system that aren't Update() either need to be made thread-safe or specified it should be called from some well-defined location. - Matt
    class NarrativePlayerSystem final : public IEcsSystem
    {
    private:
        // Nothing here yet lol. - Matt

    public:
        void Update(Timing::Timestamp delta, Catalogue catalogue) final; // update loop for the ECS. - Matt

        // These four should be inlined, if possible. - Matt
        [[nodiscard]] const std::string& GetSectionName(Atom sectionId) const;
        [[nodiscard]] Atom GetSectionName(const std::string& name) const;
        [[nodiscard]] const CharacterInformation& GetCharacterInformation(Atom characterId) const;
        [[nodiscard]] const CharacterInformation& GetCharacterInformation(const std::string& characterName) const;

        void RegisterInformationToCharacter(const std::string& name); // We will probably update/expand this as we figure out what information would be good for a CharacterInformation object. - Matt
    };
}

#endif // NOVELRT_NARRATIVEPLAYERSYSTEM_H
