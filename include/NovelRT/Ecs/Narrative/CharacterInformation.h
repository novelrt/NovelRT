#include <utility>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_CHARACTERINFORMATION_H
#define NOVELRT_CHARACTERINFORMATION_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Narrative
{
    // This type currently does not have a CPP file due to its simplicity. Feel free to add one if you end up writing logic that shouldn't be inlined.
    class CharacterInformation
    {
    private:
        Atom _characterId;
        std::string _name;

    public:
        CharacterInformation(Atom characterId, std::string name) noexcept : _characterId(characterId), _name(std::move(name))
        {
        }

        [[nodiscard]] inline Atom GetCharacterId() const noexcept
        {
            return _characterId;
        }

        [[nodiscard]] const std::string& GetName() const noexcept
        {
            return _name;
        }
    };
}

#endif // NOVELRT_CHARACTERINFORMATION_H
