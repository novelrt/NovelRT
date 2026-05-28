#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <memory>
#include <span>
#include <string>
#include <vector>

namespace NovelRT::Scripting::Statuses
{
    class Branch final : public DecisionTreeStatus
    {
        std::string _prompt;
        std::vector<std::string> _options;

    public:
        explicit Branch(const std::string& prompt,
                        const std::vector<std::string>& options,
                        lua_State* L,
                        const std::shared_ptr<ScriptManager>& manager);
        virtual ~Branch() override = default;

        Branch(const Branch&) = delete;
        Branch(Branch&&) = default;

        Branch& operator=(const Branch&) = delete;
        Branch& operator=(Branch&&) = default;

        const std::string GetPrompt() const;
        std::span<const std::string> GetOptions() const;

        std::unique_ptr<DecisionTreeStatus> Continue(size_t index);
    };
}
