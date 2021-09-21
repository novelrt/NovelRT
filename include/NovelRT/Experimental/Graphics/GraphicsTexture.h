// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSTEXTURE_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSTEXTURE_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsTexture : public GraphicsResource
    {
    private:
        GraphicsTextureKind _kind;
        uint32_t _width;
        uint32_t _height;
        uint16_t _depth;

    public:
        GraphicsTexture(std::shared_ptr<GraphicsDevice> device,
                        GraphicsTextureKind kind,
                        GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                        GraphicsResourceAccess cpuAccess,
                        uint32_t width,
                        uint32_t height,
                        uint16_t depth)
            : GraphicsResource(std::move(device), std::move(blockRegion), cpuAccess),
              _kind(kind),
              _width(width),
              _height(height),
              _depth(depth)
        {
        }

        [[nodiscard]] inline uint16_t GetDepth() const noexcept
        {
            return _depth;
        }

        [[nodiscard]] inline uint32_t GetHeight() const noexcept
        {
            return _height;
        }

        [[nodiscard]] inline GraphicsTextureKind GetKind() const noexcept
        {
            return _kind;
        }

        [[nodiscard]] inline uint32_t GetWidth() const noexcept
        {
            return _width;
        }
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSTEXTURE_H
