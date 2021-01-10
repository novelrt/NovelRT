// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_ECS_H
#define NOVELRT_ECS_H

/**
 * @brief Contains all the types required to quickly spin up NovelRT's multithreaded ECS system. Also contains ECS APIs for component management via stateless systems and other miscellaneous ECS features.
 */
namespace NovelRT::Ecs
{
}

#include "Catalogue.h"
#include "ComponentBuffer.h"
#include "ComponentCache.h"
#include "ComponentView.h"
#include "EcsUtils.h"
#include "EntityCache.h"
#include "SparseSet.h"
#include "SparseSetMemoryContainer.h"
#include "SystemScheduler.h"

#endif //!NOVELRT_ECS_H