#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Maths/GeoVector2F.hpp>
#include <NovelRT/Scripting/DecisionTreeCue.hpp>
#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

#include <memory>
#include <optional>
#include <string>

namespace NovelRT::Scripting::Statuses
{
    class TriggerCue final : public DecisionTreeStatus
    {
    private:
        // We don't own the cue; that's owned elsewhere
        const DecisionTreeCue* _cue;

    public:
        explicit TriggerCue(const DecisionTreeCue* cue,
                            lua_State* L,
                            const std::shared_ptr<ScriptManager>& manager);
        virtual ~TriggerCue() override = default;

        TriggerCue(const TriggerCue&) = delete;
        TriggerCue(TriggerCue&&) = delete;

        TriggerCue& operator=(const TriggerCue&) = delete;
        TriggerCue& operator=(TriggerCue&&) = delete;

        const DecisionTreeCue* GetCue() const;

        std::unique_ptr<DecisionTreeStatus> Continue();
    };
}
