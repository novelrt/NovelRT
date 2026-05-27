#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <memory>
#include <string>

namespace NovelRT::Scripting::Statuses
{
    class SpokenLine final : public DecisionTreeStatus
    {
        std::string _speaker;
        std::string _text;

    public:
        explicit SpokenLine(const std::string& speaker,
                            const std::string& text,
                            lua_State* L,
                            const std::shared_ptr<ScriptManager>& manager);
        virtual ~SpokenLine() override = default;

        SpokenLine(const SpokenLine&) = delete;
        SpokenLine(SpokenLine&&) = default;

        SpokenLine& operator=(const SpokenLine&) = delete;
        SpokenLine& operator=(SpokenLine&&) = default;

        const std::string GetSpeaker() const;
        const std::string GetText() const;

        std::unique_ptr<DecisionTreeStatus> Continue();
    };
}
