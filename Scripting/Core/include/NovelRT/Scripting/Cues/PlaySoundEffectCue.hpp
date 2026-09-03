#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeCue.hpp>

#include <string>

namespace NovelRT::Scripting::Cues
{
    class PlaySoundEffectCue final : public DecisionTreeCue
    {
    private:
        std::string _sound;
        double _pitch;

    public:
        explicit PlaySoundEffectCue(std::string sound, double pitch);
        virtual ~PlaySoundEffectCue() override = default;

        PlaySoundEffectCue(const PlaySoundEffectCue&) = delete;
        PlaySoundEffectCue(PlaySoundEffectCue&&) = default;

        PlaySoundEffectCue& operator=(const PlaySoundEffectCue&) = delete;
        PlaySoundEffectCue& operator=(PlaySoundEffectCue&&) = default;

        const std::string GetSound() const;
        double GetPitch() const;

        std::unique_ptr<DecisionTreeCue> Clone() const override;
    };
}
