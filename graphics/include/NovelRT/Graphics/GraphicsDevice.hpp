// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSDEVICE_H
#define NOVELRT_GRAPHICS_GRAPHICSDEVICE_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
    {
    private:
        std::weak_ptr<GraphicsAdapter> _adapter;
        std::shared_ptr<GraphicsSurfaceContext> _surfaceContext;

    protected:
        [[nodiscard]] virtual GraphicsMemoryAllocator* GetMemoryAllocatorInternal() = 0;

    public:
        GraphicsDevice(std::weak_ptr<GraphicsAdapter> adapter, std::shared_ptr<GraphicsSurfaceContext> surfaceContext)
            : _adapter(std::move(adapter)), _surfaceContext(std::move(surfaceContext))
        {
            if (_adapter.expired())
            {
                throw Exceptions::NullPointerException("The supplied GraphicsAdapter is nullptr.");
            }

            if (_surfaceContext == nullptr)
            {
                throw Exceptions::NullPointerException("The supplied GraphicsSurfaceContext is nullptr.");
            }
        }

        virtual void TearDown() = 0;

        [[nodiscard]] inline std::shared_ptr<GraphicsAdapter> GetAdapter() const
        {
            if (_adapter.expired())
            {
                throw std::runtime_error("Adapter has expired!");
            }

            return _adapter.lock();
        }

        [[nodiscard]] virtual size_t GetContextIndex() const noexcept = 0;

        [[nodiscard]] virtual NovelRT::Utilities::Misc::Span<std::shared_ptr<GraphicsContext>> GetContexts() = 0;

        [[nodiscard]] inline std::shared_ptr<GraphicsContext> GetCurrentContext()
        {
            return GetContexts()[GetContextIndex()];
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsMemoryAllocator> GetMemoryAllocator()
        {
            return std::dynamic_pointer_cast<GraphicsMemoryAllocator>(GetMemoryAllocatorInternal()->shared_from_this());
        }

        [[nodiscard]] inline std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept
        {
            return _surfaceContext->GetSurface();
        }

        [[nodiscard]] inline std::shared_ptr<GraphicsSurfaceContext> GetSurfaceContext() const noexcept
        {
            return _surfaceContext;
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipeline> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature> signature,
            std::shared_ptr<ShaderProgram> vertexShader,
            std::shared_ptr<ShaderProgram> pixelShader) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipelineSignature> CreatePipelineSignature(
            GraphicsPipelineBlendFactor srcBlendFactor,
            GraphicsPipelineBlendFactor dstBlendFactor,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineInput> inputs,
            NovelRT::Utilities::Misc::Span<GraphicsPipelineResource> resources) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPrimitive> CreatePrimitive(
            std::shared_ptr<GraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource>& indexBufferRegion,
            uint32_t indexBufferStride,
            NovelRT::Utilities::Misc::Span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions) = 0;

        [[nodiscard]] virtual std::shared_ptr<ShaderProgram> CreateShaderProgram(
            std::string entryPointName,
            ShaderProgramKind kind,
            NovelRT::Utilities::Misc::Span<uint8_t> byteData) = 0;

        virtual void PresentFrame() = 0;
        virtual void Signal(std::shared_ptr<GraphicsFence> fence) = 0;
        virtual void WaitForIdle() = 0;

        virtual ~GraphicsDevice() = default;
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSDEVICE_H
