// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSCONTEXT_H
#define NOVELRT_GRAPHICSCONTEXT_H

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
        GraphicsContext(std::shared_ptr<ILLGraphicsDevice> device, size_t index) noexcept
            : GraphicsDeviceObject(device), _index(index)
        {
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsFence> GetFence() const noexcept = 0;

        [[nodiscard]] inline size_t GetIndex() const noexcept
        {
            return _index;
        }

        virtual void BeginDrawing(NovelRT::Graphics::RGBAConfig backgroundColour) = 0;
        virtual void BeginFrame() = 0;
        virtual void Copy(std::shared_ptr<LLGraphicsBuffer> destination, std::shared_ptr<LLGraphicsBuffer> source) = 0;
        virtual void Copy(std::shared_ptr<LLGraphicsTexture> destination, std::shared_ptr<LLGraphicsBuffer> source) = 0;
        virtual void Draw(std::shared_ptr<GraphicsPrimitive> primitive) = 0;
        virtual void EndDrawing() = 0;
        virtual void EndFrame() = 0;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_GRAPHICSCONTEXT_H
