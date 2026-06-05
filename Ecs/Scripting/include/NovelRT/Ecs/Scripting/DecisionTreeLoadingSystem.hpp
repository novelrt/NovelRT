#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/IEcsSystem.hpp>

#include <NovelRT/Scripting/ScriptManager.hpp>

namespace NovelRT::Ecs::Scripting
{
    class DecisionTreeLoadingSystem : public NovelRT::Ecs::IEcsSystem
    {
    private:
        std::shared_ptr<NovelRT::Scripting::ScriptManager> _scriptManager;

    public:
        void Update(Timing::Timestamp, Catalogue);
    };
}
