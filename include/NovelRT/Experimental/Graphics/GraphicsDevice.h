// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSDEVICE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsDevice : public std::enable_shared_from_this<GraphicsDevice>
    {
    public:
        virtual void Initialise(std::shared_ptr<IGraphicsSurface> targetSurface) = 0;
        virtual void TearDown() = 0;

        [[nodiscard]] virtual std::shared_ptr<IGraphicsSurface> GetSurface() const noexcept = 0;

        [[nodiscard]] virtual std::shared_ptr<ShaderProgram> CreateShaderProgram(std::string entryPointName,
                                                                                 ShaderProgramKind kind,
                                                                                 gsl::span<uint8_t> byteData) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipeline> CreatePipeline(
            std::shared_ptr<GraphicsPipelineSignature> signature,
            std::shared_ptr<ShaderProgram> vertexShader,
            std::shared_ptr<ShaderProgram> pixelShader) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipelineSignature> CreatePipelineSignature(
            gsl::span<GraphicsPipelineInput> inputs,
            gsl::span<GraphicsPipelineResource> resources) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPrimitive> CreatePrimitive(
            std::shared_ptr<GraphicsPipeline> pipeline,
            GraphicsMemoryRegion<GraphicsResource>& vertexBufferRegion,
            uint32_t vertexBufferStride,
            GraphicsMemoryRegion<GraphicsResource> indexBufferRegion,
            uint32_t indexBufferStride,
            gsl::span<const GraphicsMemoryRegion<GraphicsResource>> inputResourceRegions) = 0;

        virtual void PresentFrame() = 0;
        virtual void Signal(std::shared_ptr<GraphicsFence> fence) = 0;
        virtual void WaitForIdle() = 0;

        virtual ~GraphicsDevice = default;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSDEVICE_H
