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
    class Configurator;
    class Catalogue;
    class ComponentBufferMemoryContainer;
    class ComponentCache;
    class EntityCache;
    class IEcsSystem;
    class SparseSetMemoryContainer;
    class SystemScheduler;
    class UnsafeComponentView;
    struct TransformComponent;
}

// dependencies for ECS
// clang-format off
#include "../Atom.h"
#include "../Exceptions/Exceptions.h"
#include "../Maths/Maths.h"
#include "../Timing/Timestamp.h"
#include "../Utilities/Event.h"
#include "../Utilities/KeyValuePair.h"
#include "../PluginManagement/PluginManagement.h"
#include "../Experimental/Threading/Threading.h"
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iterator>
#include <memory>
#include <optional>
#include <queue>
#include <thread>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>
#include <map>
#ifndef __TBB_PREVIEW_MUTEXES
#define __TBB_PREVIEW_MUTEXES 1
#endif
#include <oneapi/tbb/mutex.h>

// clang-format on

// ECS types

// clang-format off

#include "EcsUtils.h"
#include "SparseSetMemoryContainer.h"
#include "SparseSet.h"
#include "ComponentBufferMemoryContainer.h"
#include "ComponentBuffer.h"
#include "ComponentCache.h"
#include "ComponentView.h"
#include "EcsUtils.h"
#include "EntityCache.h"
#include "IEcsSystem.h"
#include "Catalogue.h"
#include "SystemScheduler.h"
#include "UnsafeComponentView.h"
#include "Graphics/Ecs.Graphics.h"
#include "DefaultComponentTypes.h"
#include "Audio/Ecs.Audio.h"
#include "Configurator.h"

// clang-format on

#endif //! NOVELRT_ECS_H