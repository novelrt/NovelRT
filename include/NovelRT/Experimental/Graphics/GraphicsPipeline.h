// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSPIPELINE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSPIPELINE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsPipeline : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsPipelineSignature> _signature;
        std::shared_ptr<ShaderProgram> _vertexShader;
        std::shared_ptr<ShaderProgram> _pixelShader;

    public:
        GraphicsPipeline(std::shared_ptr<GraphicsDevice> device,
                         std::shared_ptr<GraphicsPipelineSignature> signature,
                         std::shared_ptr<ShaderProgram> vertexShader,
                         std::shared_ptr<ShaderProgram> pixelShader) noexcept;

        [[nodiscard]] bool HasVertexShader() const noexcept;
        [[nodiscard]] bool HasPixelShader() const noexcept;
        [[nodiscard]] std::shared_ptr<ShaderProgram> GetVertexShader() const noexcept;
        [[nodiscard]] std::shared_ptr<ShaderProgram> GetPixelShader() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature> GetSignature() const noexcept;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSPIPELINE_H
