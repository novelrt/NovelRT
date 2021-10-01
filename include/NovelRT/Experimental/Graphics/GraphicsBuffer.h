// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSBUFFER_H
#define NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSBUFFER_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsBuffer : public GraphicsResource
    {
    private:
        GraphicsBufferKind _kind;

    public:
        GraphicsBuffer(std::shared_ptr<GraphicsDevice> device,
                       GraphicsBufferKind kind,
                       GraphicsMemoryRegion<GraphicsMemoryBlock> blockRegion,
                       GraphicsResourceAccess cpuAccess)
            : GraphicsResource(std::move(device), std::move(blockRegion), cpuAccess), _kind(kind)
        {
        }

        [[nodiscard]] inline GraphicsBufferKind GetKind() const noexcept
        {
            return _kind;
        }
    };
} 

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICS_GRAPHICSBUFFER_H
