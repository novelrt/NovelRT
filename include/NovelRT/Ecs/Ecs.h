// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_H
#define NOVELRT_ECS_H

/**
 * @brief Contains all the types required to quickly spin up NovelRT's multithreaded ECS system. Also contains ECS APIs
 * for component management via stateless systems and other miscellaneous ECS features.
 */
namespace NovelRT::Ecs
{
    class Catalogue;
    class ComponentBufferMemoryContainer;
    class ComponentCache;
    class EntityCache;
    class SparseSetMemoryContainer;
    class SystemScheduler;
    class UnsafeComponentView;
} // namespace NovelRT::Ecs

// dependencies for ECS
#include "../Atom.h"
#include "../Exceptions/Exceptions.h"
#include "../Timing/Timestamp.h"
#include "../Utilities/Event.h"
#include "../Utilities/KeyValuePair.h"
#include "EcsUtils.h"
#include "SparseSetMemoryContainer.h"
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iterator>
#include <memory>
#include <mutex>
#include <thread>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

// ECS types
#include "Catalogue.h"
#include "ComponentBufferMemoryContainer.h"
#include "ComponentBuffer.h"
#include "ComponentCache.h"
#include "ComponentView.h"
#include "EcsUtils.h"
#include "EntityCache.h"
#include "SparseSetMemoryContainer.h"
#include "SparseSet.h"
#include "SystemScheduler.h"
#include "UnsafeComponentView.h"

#endif //! NOVELRT_ECS_H