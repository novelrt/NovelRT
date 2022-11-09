// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_UI_UISYSTEM_H
#define NOVELRT_ECS_UI_UISYSTEM_H

#ifndef NOVELRT_ECS_UI_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.UI.h instead for the Ecs.UI namespace subset.
#endif

namespace NovelRT::Ecs::UI
{
    class UISystem : public Ecs::IEcsSystem
    {
    private:
        struct CmdSubmissionInfo
        {
            uint32_t vertexOffset;
            uint32_t indexOffset;
            uint32_t elementCount;
            NovelRT::Graphics::GraphicsMemoryRegion<NovelRT::Graphics::GraphicsResource> textureData;
        };

        struct CmdListSubmissionInfo
        {
            Threading::FutureResult<Graphics::VertexInfo> Vertices = Threading::FutureResult<Graphics::VertexInfo>(nullptr, Graphics::VertexInfo{});
            Threading::FutureResult<Graphics::VertexInfo> Indices = Threading::FutureResult<Graphics::VertexInfo>(nullptr, Graphics::VertexInfo{});
            std::vector<CmdSubmissionInfo> Cmds;
        };


        LoggingService _logger;
        std::shared_ptr<NovelRT::UI::UIProvider> _uiProvider;
        std::shared_ptr<Ecs::Graphics::DefaultRenderingSystem> _defaultRenderingSystem;
        std::shared_ptr<NovelRT::Graphics::GraphicsPipeline> _uiPipeline;
        tbb::mutex _submissionInfoListMutex;
        std::queue<std::vector<CmdListSubmissionInfo>> _submissionInfoListQueue;
        std::vector<Threading::FutureResult<Graphics::VertexInfo>> _gpuObjectsToCleanUp;

        size_t _drawCallCounter;

    public:
        UISystem(std::shared_ptr<PluginManagement::IUIPluginProvider> uiPluginProvider,
                 std::shared_ptr<PluginManagement::IWindowingPluginProvider> windowingPluginProvider,
                 std::shared_ptr<PluginManagement::IInputPluginProvider> inputPluginProvider,
                 std::shared_ptr<PluginManagement::IResourceManagementPluginProvider> resourceManagementPluginProvider,
                 std::shared_ptr<Graphics::DefaultRenderingSystem> defaultRenderingSystem);

        Utilities::Event<std::reference_wrapper<UISystem>, Timing::Timestamp, Ecs::Catalogue> Draw;

        void Update(Timing::Timestamp delta, Ecs::Catalogue catalogue) final;
    };
}

#endif // NOVELRT_ECS_INPUT_INPUTSYSTEM_H
