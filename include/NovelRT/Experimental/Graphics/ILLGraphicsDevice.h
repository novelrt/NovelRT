// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_ILLGRAPHICSDEVICE_H
#define NOVELRT_EXPERIMENTAL_ILLGRAPHICSDEVICE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class ILLGraphicsDevice : public std::enable_shared_from_this<ILLGraphicsDevice>
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
            std::shared_ptr<ShaderProgram> vertexShader = nullptr,
            std::shared_ptr<ShaderProgram> pixelShader = nullptr) = 0;

        [[nodiscard]] virtual std::shared_ptr<GraphicsPipelineSignature> CreatePipelineSignature(
            gsl::span<GraphicsPipelineInput> inputs = gsl::span<GraphicsPipelineInput>{},
            gsl::span<GraphicsPipelineResource> resources = gsl::span<GraphicsPipelineResource>{}) = 0;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_ILLGRAPHICSDEVICE_H
