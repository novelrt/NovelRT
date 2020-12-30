
// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_COMPONENTVIEW_H
#define NOVELRT_ECS_COMPONENTVIEW_H

#include "EcsUtils.h"
#include "ComponentBuffer.h"

namespace NovelRT::Ecs
{
    template <typename TComponent>
    class ComponentView
    {
        private:
        size_t _poolId;
        ComponentBuffer<TComponent>& _componentBuffer;
        
        public:
        ComponentView(size_t poolId, ComponentBuffer<TComponent>& targetBuffer) noexcept : _poolId(poolId),
                                                                                           _componentBuffer(targetBuffer)
        {

        }

        void PushComponentUpdateInstruction(EntityId entity, TComponent instructionState) noexcept
        {
            _componentBuffer.PushComponentUpdateInstruction(_poolId, entity, instructionState);
        }

        void AddComponent(EntityId entity, TComponent initialValue = TComponent{}) noexcept
        {
            PushComponentUpdateInstruction(entity, initialValue);
        }

        void RemoveComponent(EntityId entity) noexcept
        {
            PushComponentUpdateInstruction(entity, _componentBuffer.GetDeleteInstructionState());
        }

        bool TryAddComponent(EntityId entity, TComponent initialValue = TComponent{}) noexcept
        {
            if (_componentBuffer.HasComponent(entity))
            {
                return false;
            }

            AddComponent(entity, initialValue);
            return true;
        }

        bool TryRemoveComponent(EntityId entity)
        {
            if (!_componentBuffer.HasComponent(entity))
            {
                return false;
            }

            RemoveComponent(entity);
            return true;
        }

        [[nodiscard]] TComponent GetComponent(EntityId entity) const
        {
            return _componentBuffer.GetComponent(entity);
        }

        [[nodiscard]] size_t GetImmutableDataLength() const noexcept
        {
            return _componentBuffer.GetImmutableDataLength();
        }

        // clang-format off
        [[nodiscard]] auto begin() const noexcept
        {
            return _componentBuffer.begin();
        }

        [[nodiscard]] auto end() const noexcept
        {
            return _componentBuffer.end();
        }
        // clang-format on
    };
}

#endif //!NOVELRT_ECS_COMPONENTVIEW_H