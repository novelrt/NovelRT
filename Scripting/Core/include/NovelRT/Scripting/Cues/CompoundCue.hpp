#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeCue.hpp>

#include <memory>
#include <ranges>
#include <span>
#include <vector>

namespace NovelRT::Scripting::Cues
{
    class CompoundCue final : public DecisionTreeCue
    {
    private:
        std::vector<std::unique_ptr<DecisionTreeCue>> _cues;

    public:
        explicit CompoundCue(std::vector<std::unique_ptr<DecisionTreeCue>>&& cues);
        virtual ~CompoundCue() override = default;

        CompoundCue(const CompoundCue&) = delete;
        CompoundCue(CompoundCue&&) = default;

        CompoundCue& operator=(const CompoundCue&) = delete;
        CompoundCue& operator=(CompoundCue&&) = default;

        // N.B. This needs to be declared here because ranges are weird.
        std::ranges::view auto children() const
        {
            return _cues | std::views::transform([](const auto& it){ return it.get(); });
        };

        std::unique_ptr<DecisionTreeCue> Clone() const override;
    };
}
