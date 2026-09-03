#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Scripting
{
    class DecisionTreeCue
    {
    public:
        explicit DecisionTreeCue() = default;
        virtual ~DecisionTreeCue() = default;

        DecisionTreeCue(const DecisionTreeCue&) = delete;
        DecisionTreeCue(DecisionTreeCue&&) = default;

        DecisionTreeCue& operator=(const DecisionTreeCue&) = delete;
        DecisionTreeCue& operator=(DecisionTreeCue&&) = default;

        virtual std::unique_ptr<DecisionTreeCue> Clone() const = 0;
    };
}
