// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_SYSTEMSCHEDULER_H
#define NOVELRT_ECS_SYSTEMSCHEDULER_H

#include "EcsUtils.h"
#include "../Atom.h"
#include "../Timing/Timestamp.h"
#include <unordered_map>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <vector>

namespace NovelRT::Ecs
{
    class SystemScheduler
    {
    private:
        struct SystemRecord
        {
            std::function<void(Timing::Timestamp)> systemPtr;
            std::vector<Atom> dependencies;
        };

        struct QueueLockPair
        {
            std::vector<Atom> systemIds;
            std::mutex threadLock;
        };

        //volatile, atomic operations, std atomic uint64_t

        std::vector<Atom> _independentSystemIds;

        static inline const uint32_t DEFAULT_BLIND_THREAD_LIMIT = 8;

        std::unordered_map<Atom, SystemRecord> _systems;
        uint32_t _maximumThreadCount;

        std::vector<QueueLockPair> _threadWorkQueues;
        std::vector<std::thread> _threadCache; //TODO: is this needed?
        
        Timing::Timestamp _currentDelta;

        std::atomic_uint64_t _threadAvailabilityMap;

        bool JobAvailable(size_t poolId) noexcept;
        void CyleForJob(size_t poolId);

    public:
        SystemScheduler(uint32_t maximumThreadCount = 0);

        template <typename TComponent>
        Atom GetSystemIdForComponent()
        {
            static const Atom id = Atom::getNextComponentTypeId();
            return id;
        }

        template <typename TComponent>
        Atom RegisterSystemForComponent(std::function<void(Timing::Timestamp)> systemPtr, std::vector<Atom> dependencies = std::vector<Atom>())
        {
            Atom returnId = GetComponentSystemId<TComponent>();
            _systems.emplace(returnId, SystemRecord{systemPtr, dependencies});

            if (dependencies.size() == 0)
            {
                _independentSystemIds.emplace_back(returnId);
            }

            return returnId;
        }

        void ExecuteIteration(Timing::Timestamp delta);
    };
} 

#endif //!NOVELRT_ECS_SYSTEMSCHEDULER_H