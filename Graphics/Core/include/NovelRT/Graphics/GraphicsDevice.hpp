#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsPipelineBlendFactor.hpp>
#include <NovelRT/Graphics/GraphicsPushConstantRange.hpp>
#include <NovelRT/Graphics/GraphicsSurfaceContext.hpp>
#include <NovelRT/Graphics/IGraphicsSurface.hpp>
#include <NovelRT/Graphics/ShaderProgramKind.hpp>
#include <NovelRT/Utilities/Lazy.hpp>
#include <NovelRT/Utilities/Span.hpp>

#include <memory>
#include <stdexcept>

namespace NovelRT::Graphics
{
    template<typename TBackend> class GraphicsAdapter;
    template<typename TBackend> class GraphicsFence;
    template<typename TBackend> class GraphicsSurfaceContext;
    template<typename TBackend> class GraphicsContext;
    template<typename TBackend> class GraphicsPipeline;
    template<typename TBackend> class GraphicsDevice;
    template<typename TBackend> class GraphicsRenderPass;
    class GraphicsPipelineInput;
    class GraphicsPipelineResource;
    template<typename TBackend> class GraphicsPipelineSignature;
    template<typename TBackend> class ShaderProgram;

    template<typename TBackend> class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice<TBackend>>
    {
    public:
        using iterator = typename std::vector<std::shared_ptr<GraphicsContext<TBackend>>>::iterator;
        using const_iterator = typename std::vector<std::shared_ptr<GraphicsContext<TBackend>>>::const_iterator;

        GraphicsDevice() = delete;

        [[nodiscard]] std::shared_ptr<GraphicsAdapter<TBackend>> GetAdapter() const;

        [[nodiscard]] size_t GetContextIndex() const noexcept;

        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator begin() noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator begin() const noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] iterator end() noexcept;
        // NOLINTNEXTLINE(readability-identifier-naming) - stdlib compatibility
        [[nodiscard]] const_iterator end() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsContext<TBackend>> GetCurrentContext() const;
        [[nodiscard]] std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsSurfaceContext<TBackend>> GetSurfaceContext() const noexcept;

        [[nodiscard]] std::shared_ptr<GraphicsPipeline<TBackend>> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature<TBackend>> signature,
            std::shared_ptr<ShaderProgram<TBackend>> vertexShader,
            std::shared_ptr<ShaderProgram<TBackend>> pixelShader,
            bool imguiRenderMode = false);

        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature<TBackend>> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Span<GraphicsPipelineResource> resources,
            NovelRT::Utilities::Span<GraphicsPushConstantRange> pushConstantRanges);

        [[nodiscard]] std::shared_ptr<GraphicsRenderPass<TBackend>> GetRenderPass();

        [[nodiscard]] std::shared_ptr<ShaderProgram<TBackend>> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Span<uint8_t> byteData);

        void PresentFrame();

        void Signal(const GraphicsContext<TBackend>* context);

        void WaitForIdle();
    };
}
