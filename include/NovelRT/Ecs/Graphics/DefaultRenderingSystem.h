// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
#define NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs::Graphics
{
    class DefaultRenderingSystem : public IEcsSystem
    {
    private:
        std::shared_ptr<PluginManagement::IGraphicsPluginProvider> _graphicsPluginProvider;
        std::shared_ptr<PluginManagement::IWindowingPluginProvider> _windowingPluginProvider;
        SceneGraph::Scene _renderScene;

    public:
        DefaultRenderingSystem(std::shared_ptr<PluginManagement::IGraphicsPluginProvider> graphicsPluginProvider,
                               std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider);

        void RenderUpdate(Timing::Timestamp delta, Ecs::Catalogue catalogue);
    };
}

#endif // !NOVELRT_ECS_GRAPHICS_DEFAULTRENDERINGSYSTEM_H
