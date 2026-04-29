#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

namespace NovelRT::Scripting
{
    class DecisionTreeResult
    {
        // Reference created with luaL_ref
        int reference;

    public:
        explicit DecisionTreeResult();
        ~DecisionTreeResult() = default;

        DecisionTreeResult(const DecisionTreeResult&) = delete;
        DecisionTreeResult(DecisionTreeResult&&) = default;

        DecisionTreeResult& operator=(const DecisionTreeResult&) = delete;
        DecisionTreeResult& operator=(DecisionTreeResult&&) = default;

        std::unique_ptr<DecisionTreeResult> Continue();
    };
}
