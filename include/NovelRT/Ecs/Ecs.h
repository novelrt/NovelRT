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
}

//dependencies for ECS
#include <atomic>
#include <algorithm>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <typeindex>
#include <tuple>
#include <utility>
#include <mutex>
#include <thread>
#include "../Utilities/Event.h"
#include "../Exceptions/Exceptions.h"
#include "../Atom.h"
#include "../Utilities/KeyValuePair.h"
#include "EcsUtils.h"
#include "SparseSetMemoryContainer.h"
#include "../Timing/Timestamp.h"

//ECS types
#include "EcsUtils.h"
#include "SparseSetMemoryContainer.h"
#include "SparseSet.h"
#include "ComponentBufferMemoryContainer.h"
#include "ComponentBuffer.h"
#include "ComponentView.h"
#include "ComponentCache.h"
#include "Catalogue.h"
#include "EntityCache.h"
#include "SystemScheduler.h"
#include "UnsafeComponentView.h"

#endif //! NOVELRT_ECS_H