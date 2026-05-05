// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Scripting/DecisionTreeStatus.hpp>
#include <NovelRT/Scripting/ScriptManager.hpp>

NovelRT::Scripting::DecisionTreeStatus::DecisionTreeStatus(lua_State* L, const std::shared_ptr<ScriptManager>& manager)
    : _state(L),
      _manager(std::move(manager))
{ }
