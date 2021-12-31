// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_ENTITYOBJECT_H
#define NOVELRT_ECS_ENTITYOBJECT_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    class EntityObject
    {
    private:
        EntityId _entity;
        Catalogue& _catalogue;
        std::optional<std::reference_wrapper<EntityObject>> _parent;
        Utilities::Lazy<std::vector<EntityObject>> _children;

    public:
        EntityObject(EntityId entity, Catalogue& catalogue);

        template<typename TComponent>
        [[nodiscard]] TComponent Get() const
        {
            auto componentView = _catalogue.GetComponentView<TComponent>();
            return GetNonAlloc<TComponent>(componentView);
        }

        template<typename TComponent>
        [[nodiscard]] TComponent GetNonAlloc(const ComponentView<TComponent>& componentView) const
        {
            return componentView.GetComponent<TComponent>(_entity);
        }

        [[nodiscard]] inline bool IsRootEntity() const noexcept
        {
            return _parent.has_value();
        }

        [[nodiscard]] EntityObject& GetParent() const noexcept;
        [[nodiscard]] LinkedEntityListView GetChildren();
    };
}

#endif // NOVELRT_ECS_ENTITYOBJECT_H
