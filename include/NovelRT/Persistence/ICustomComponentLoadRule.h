// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_PERSISTENCE_ICUSTOMCOMPONENTLOADRULE_H
#define NOVELRT_PERSISTENCE_ICUSTOMCOMPONENTLOADRULE_H

#ifndef NOVELRT_PERSISTENCE_H
#error NovelRT does not support including types explicitly by default. Please include Persistence.h instead for the Persistence namespace subset.
#endif

namespace NovelRT::Persistence
{
    class ICustomComponentLoadRule
    {
    public:
        virtual ~ICustomComponentLoadRule() = default;

        virtual void ExecuteComponentLoadModification(const Ecs::SparseSet<Ecs::EntityId, Ecs::EntityId>& localToGlobalEntityMap, void* componentDataHandle) = 0;
    };
}

#endif // NOVELRT_PERSISTENCE_ICUSTOMCOMPONENTLOADRULE_H
