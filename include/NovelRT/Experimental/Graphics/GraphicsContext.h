// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSCONTEXT_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSCONTEXT_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsContext : public GraphicsDeviceObject
    {
    private:
        size_t _index;

    public:
        GraphicsContext(const std::shared_ptr<GraphicsDevice>& device, size_t index) noexcept
            : GraphicsDeviceObject(std::weak_ptr<GraphicsDevice>(device)), _index(index)
        {
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsFence> GetFence() const noexcept = 0;

        [[nodiscard]] inline size_t GetIndex() const noexcept
        {
            return _index;
        }

        virtual void BeginDrawing(NovelRT::Graphics::RGBAColour backgroundColour) = 0;
        virtual void BeginFrame() = 0;
        virtual void Copy(std::shared_ptr<GraphicsBuffer> destination, std::shared_ptr<GraphicsBuffer> source) = 0;
        virtual void Copy(std::shared_ptr<GraphicsTexture> destination, std::shared_ptr<GraphicsBuffer> source) = 0;

        inline void Draw(std::shared_ptr<GraphicsPrimitive> primitive)
        {
            Draw(std::move(primitive), 1);
        }

        virtual void Draw(std::shared_ptr<GraphicsPrimitive> primitive, uint32_t instanceCount) = 0;
        virtual void EndDrawing() = 0;
        virtual void EndFrame() = 0;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSCONTEXT_H
