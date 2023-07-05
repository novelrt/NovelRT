#pragma once

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Graphics/GraphicsDeviceObject.hpp>

namespace NovelRT::Graphics
{
    class GraphicsPipeline : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsPipelineSignature> _signature;
        std::shared_ptr<ShaderProgram> _vertexShader;
        std::shared_ptr<ShaderProgram> _pixelShader;

    public:
        GraphicsPipeline(const std::shared_ptr<GraphicsDevice>& device,
                         std::shared_ptr<GraphicsPipelineSignature> signature,
                         std::shared_ptr<ShaderProgram> vertexShader,
                         std::shared_ptr<ShaderProgram> pixelShader) noexcept;

        [[nodiscard]] bool HasVertexShader() const noexcept;
        [[nodiscard]] bool HasPixelShader() const noexcept;
        [[nodiscard]] std::shared_ptr<ShaderProgram> GetVertexShader() const noexcept;
        [[nodiscard]] std::shared_ptr<ShaderProgram> GetPixelShader() const noexcept;
        [[nodiscard]] std::shared_ptr<GraphicsPipelineSignature> GetSignature() const noexcept;
    };
}
