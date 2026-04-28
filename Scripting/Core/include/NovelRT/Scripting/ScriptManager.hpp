#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <memory>

typedef struct lua_State lua_State;

namespace NovelRT::Scripting
{
    class ScriptManager
    {
    private:
        struct CloseState {
            void operator()(lua_State*);
        };

        std::unique_ptr<lua_State, CloseState> _state;

    public:
        explicit ScriptManager();
        ~ScriptManager() = default;

        ScriptManager(const ScriptManager&) = delete;
        ScriptManager(ScriptManager&&) = default;

        ScriptManager& operator=(const ScriptManager&) = delete;
        ScriptManager& operator=(ScriptManager&&) = default;

        // Some thinking...
        // DecisionTree LoadDecisionTree(SomeTextResource resource);
    };

    // Some thinking...
    /*
     * struct DecisionTree
     * {
     *     Result Begin(); // Begins a new instance of this decision tree - only one can run at a time though multiple can be in progress.
     *                     // Returns a polymorphic type (see below) indicating the current state.
     *     // Maybe retain a list of active decision trees?
     * };
     *
     * struct TextResult
     * {
     *     std::string Speaker;
     *     std::string Text;
     *     Result Continue();
     * };
     *
     * struct BranchResult
     * {
     *     std::vector<std::string> Branches; // Branch keys
     *     Result Continue(std::string branch);
     * };
     *
     * In the future there may be additional types...
     */
}
