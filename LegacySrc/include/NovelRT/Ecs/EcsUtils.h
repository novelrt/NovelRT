// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_ECSUTILS_H
#define NOVELRT_ECS_ECSUTILS_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    using EntityId = NovelRT::Atom;
    using ComponentTypeId = NovelRT::Atom;

    std::unordered_map<std::type_index, ComponentTypeId>& GetComponentTypeIds() noexcept;

    /**
     * @brief Retrieves the ComponentTypeId for a given component type.
     *
     * This free function will create a new ID for the given type if one does not exist on the first call.
     *
     * @tparam TComponent The component type to get the ID for.
     * @return The numerical ID of the component type as an Atom.
     */
    template<typename TComponent>[[nodiscard]] ComponentTypeId GetComponentTypeId() noexcept
    {
        static_assert(
            std::is_trivially_copyable<TComponent>::value,
            "Component type must be trivially copyable for use with a ComponentTypeId. See the documentation for "
            "more information.");

        static AtomFactory& _componentTypeIdFactory = AtomFactoryDatabase::GetFactory("ComponentTypeId");

        auto& componentTypeId = GetComponentTypeIds()[typeid(TComponent)];

        if (componentTypeId == Atom(0))
        {
            componentTypeId = _componentTypeIdFactory.GetNext();
        }
        return componentTypeId;
    }
}

#endif //! NOVELRT_ECS_ECSUTILS_H
