// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_BASESYSTEM_H
#define NOVELRT_ECS_BASESYSTEM_H

#include "EcsUtils.h"
#include "../Atom.h"
#include "../Timing/Timestamp.h"
#include "SparseSet.h"
#include <vector>
#include <thread>
#include <map>
#include <queue>

namespace NovelRT::Ecs
{
    enum class ComponentUpdateType : int32_t
    {
        Add = 0,
        Remove = 1
    };

    template<typename T>
    class BaseSystem
    {
        friend class SystemScheduler;

        private:
        struct EntityComponentUpdateObject
        {
            ComponentUpdateType updateType;
            EntityId id;
            T componentData;
        };

        std::vector<SparseSet<EntityId, T>> _ecsDataBuffers;
        std::map<std::thread::id, std::vector<EntityComponentUpdateObject>> _componentUpdateInstructions;

        static inline const size_t MutableBufferId = 0;
        static inline const size_t ImmutableBufferId = 1;

        void UpdateComponentBuffer(Timing::Timestamp deltaTime)
        {
            UpdateComponents(deltaTime, _ecsDataBuffers.at(MutableBufferId));
        }

        void ValidateCacheForThread() noexcept
        {
            if (_componentUpdateInstructions.find(std::this_thread::get_id()) == _componentUpdateInstructions.end())
            {
                _componentUpdateInstructions.emplace(std::this_thread::get_id(), std::vector<EntityComponentUpdateObject>{});
            }
        }

        void PrepComponentBuffers()
        {
            for (auto &&pair : _componentUpdateInstructions)
            {
                for (auto &&instruction : pair.second)
                {
                    switch (instruction.updateType)
                    {
                    case ComponentUpdateType::Add:
                        _ecsDataBuffers.at(MutableBufferId).Insert(instruction.id, instruction.componentData);
                        break;
                    
                    case ComponentUpdateType::Remove:
                        _ecsDataBuffers.at(MutableBufferId).Remove(instruction.id);
                        break;

                    default:
                        break;
                    }
                }
                pair.second.clear();
            }

            _ecsDataBuffers.at(ImmutableBufferId) = SparseSet<EntityId, T>(_ecsDataBuffers.at(MutableBufferId));
        }

        protected:
        virtual void UpdateComponents(Timing::Timestamp deltaTime, SparseSet<EntityId, T>& componentData) = 0;

        public:
        BaseSystem() : _ecsDataBuffers(std::vector<SparseSet<EntityId, T>>{SparseSet<EntityId, T>{}, SparseSet<EntityId, T>{}})
        {

        }

        void AddComponent(T component, EntityId entity) noexcept
        {
            ValidateCacheForThread();
            EntityComponentUpdateObject objectToPass { ComponentUpdateType::Add, entity, component };
            _componentUpdateInstructions[std::this_thread::get_id()].emplace_back(objectToPass);
        }

        void RemoveComponent(EntityId entity)
        {
            if (!_ecsDataBuffers.at(ImmutableBufferId).ContainsKey(entity))
            {
                throw std::runtime_error("Component not found for entity " + entity);
            }
            
            ValidateCacheForThread();
            EntityComponentUpdateObject objectToPass { ComponentUpdateType::Remove, entity, T{} };
            _componentUpdateInstructions[std::this_thread::get_id()].emplace_back(objectToPass);
        }

        T GetComponent(EntityId entity) const
        {
            return _ecsDataBuffers.at(ImmutableBufferId).GetImmutableView()[entity];
        }

        bool HasComponent(EntityId entity) const noexcept
        {
            return _ecsDataBuffers.at(ImmutableBufferId).ContainsKey(entity);
        }
    };
}

#endif //!NOVELRT_ECS_BASESYSTEM_H