#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeCue.hpp>

#include <string>

namespace NovelRT::Scripting::Cues
{
    class SetPoseCue final : public DecisionTreeCue
    {
    private:
        std::string _character;
        std::string _pose;

    public:
        explicit SetPoseCue(std::string character, std::string pose);
        virtual ~SetPoseCue() override = default;

        SetPoseCue(const SetPoseCue&) = delete;
        SetPoseCue(SetPoseCue&&) = default;

        SetPoseCue& operator=(const SetPoseCue&) = delete;
        SetPoseCue& operator=(SetPoseCue&&) = default;

        const std::string GetCharacter() const;
        const std::string GetPose() const;

        std::unique_ptr<DecisionTreeCue> Clone() const override;
    };
}
