#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsPipelineBlendFactor.hpp>
#include <NovelRT/Graphics/GraphicsPushConstantRange.hpp>
#include <NovelRT/Graphics/GraphicsRenderPassDescription.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>
#include <NovelRT/Graphics/ShaderProgramKind.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <stdexcept>

namespace NovelRT::Graphics
{
    template<typename TBackend>
    class GraphicsAdapter;
    template<typename TBackend>
    class GraphicsSurfaceContext;
    template<typename TBackend>
    class GraphicsContext;
    template<typename TBackend>
    class GraphicsCmdList;
    template<typename TBackend>
    class GraphicsPipeline;
    template<typename TBackend>
    class GraphicsDevice;
    template<typename TBackend>
    class GraphicsRenderPass;
    class GraphicsPipelineInput;
    class GraphicsPipelineResource;
    template<typename TBackend>
    class GraphicsPipelineSignature;
    template<typename TBackend>
    class ShaderProgram;
    template<typename TBackend>
    class GraphicsSemaphore;
    template<typename TBackend>
    class GraphicsSwapchain;
    template<typename TBackend>
    class GraphicsSwapchainImage;

    template<typename TBackend>
    class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice<TBackend>>
    {
    public:
        GraphicsDevice() = delete;

        [[nodiscard]] std::shared_ptr<GraphicsAdapter<TBackend>> GetAdapter() const;

        [[nodiscard]] std::shared_ptr<GraphicsSwapchain<TBackend>> GetSwapchain() const;

        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsSurfaceContext<TBackend>> GetSurfaceContext() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsSemaphore<TBackend>> CreateSemaphore(
            uint64_t initialValue = std::numeric_limits<uint64_t>::max());

        [[nodiscard]] std::shared_ptr<GraphicsPipeline<TBackend>> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature,
            std::shared_ptr<ShaderProgram<TBackend>> vertexShader,
            std::shared_ptr<ShaderProgram<TBackend>> pixelShader,
            std::shared_ptr<GraphicsRenderPass<TBackend>> renderPass,
            bool imguiRenderMode = false);

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature<TBackend>> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<GraphicsPushConstantRange> pushConstantRanges);

        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Span<uint8_t> byteData);

        [[nodiscard]] std::shared_ptr<GraphicsContext<TBackend>> CreateGraphicsContext();

        [[nodiscard]] std::shared_ptr<GraphicsSwapchainImage<TBackend>> BeginFrame();
        void EndFrame();

        void QueueSubmit(NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<TBackend>>> cmdLists);

        void QueueSubmit(NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<TBackend>>> cmdLists,
                         NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<TBackend>>, uint64_t>>
                             semaphoresToSignal);
        void QueueSubmit(NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<TBackend>>, uint64_t>>
                             semaphoresToWait,
                         NovelRT::Utilities::Span<std::shared_ptr<GraphicsCmdList<TBackend>>> cmdLists,
                         NovelRT::Utilities::Span<std::pair<std::shared_ptr<GraphicsSemaphore<TBackend>>, uint64_t>>
                             semaphoresToSignal);

        void WaitForIdle();

        [[nodiscard]] std::shared_ptr<GraphicsRenderPass<TBackend>> CreateRenderPass(
            const GraphicsRenderPassDescription& description);
    };
}
