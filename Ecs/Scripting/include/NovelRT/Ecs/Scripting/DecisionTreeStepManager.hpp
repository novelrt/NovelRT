#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/EcsUtils.hpp>

#include <NovelRT/Utilities/Atom.hpp>

#include <functional>
#include <map>
#include <memory>
#include <set>

namespace NovelRT::Scripting
{
    class DecisionTreeStatus;
}

namespace NovelRT::Ecs
{
    class Catalogue;
}

namespace NovelRT::Ecs::Scripting
{
    class EcsScriptingBuilder;

    using DecisionTreeStepKind = NovelRT::Atom;

    class DecisionTreeStepManager
    {
    private:
        using StepHandler = std::function<void(NovelRT::Ecs::Catalogue&,EntityId,std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&)>;
        using Tuple = std::tuple<StepHandler, DecisionTreeStepKind>;
        struct Compare
        {
            constexpr bool operator()(const Tuple& lhs, const Tuple& rhs) const
            {
                std::less<DecisionTreeStepKind> impl{};
                return impl(std::get<DecisionTreeStepKind>(lhs), std::get<DecisionTreeStepKind>(rhs));
            }
        };

        std::set<Tuple, Compare> _registeredStepHandlers;
        std::map<DecisionTreeStepKind, std::function<void(NovelRT::Ecs::Catalogue&,EntityId,std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&)>> _reverseStepHandlerMapping;

        explicit DecisionTreeStepManager();

        friend EcsScriptingBuilder;

    public:
        DecisionTreeStepManager(const DecisionTreeStepManager& other) = default;
        DecisionTreeStepManager& operator=(const DecisionTreeStepManager& other) = default;
        DecisionTreeStepManager(DecisionTreeStepManager&& other) = default;
        DecisionTreeStepManager& operator=(DecisionTreeStepManager&& other) = default;
        ~DecisionTreeStepManager() = default;

        DecisionTreeStepKind RegisterStepHandler(std::function<void(NovelRT::Ecs::Catalogue&,EntityId,std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&)>);

        const std::function<void(NovelRT::Ecs::Catalogue&,EntityId,std::shared_ptr<NovelRT::Scripting::DecisionTreeStatus>&)>& GetStepHandler(DecisionTreeStepKind id) const;
    };
}
