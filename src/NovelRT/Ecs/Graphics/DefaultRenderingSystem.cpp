// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>
#include <NovelRT/Ecs/Graphics/DefaultRenderingSystem.h>

namespace NovelRT::Ecs::Graphics
{
    DefaultRenderingSystem::DefaultRenderingSystem(
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider)
        : _graphicsPluginProvider(std::move(graphicsPluginProvider)),
          _windowingPluginProvider(std::move(windowingPluginProvider))
    {
        
    }

    void DefaultRenderingSystem::RenderUpdate(Timing::Timestamp delta, Ecs::Catalogue catalogue)
    {
    }
}
