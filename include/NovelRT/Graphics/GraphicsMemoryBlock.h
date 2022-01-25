// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_GRAPHICSMEMORYBLOCK_H
#define NOVELRT_GRAPHICS_GRAPHICSMEMORYBLOCK_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    class GraphicsMemoryBlock : public GraphicsDeviceObject, public IGraphicsMemoryRegionCollection<GraphicsMemoryBlock>
    {
    private:
        std::shared_ptr<GraphicsMemoryBlockCollection> _collection;

    public:
        GraphicsMemoryBlock(std::shared_ptr<GraphicsDevice> device,
                            std::shared_ptr<GraphicsMemoryBlockCollection> collection);

        [[nodiscard]] inline std::shared_ptr<GraphicsMemoryBlockCollection> GetCollection() const noexcept
        {
            return _collection;
        }

        ~GraphicsMemoryBlock() override = default;
    };
}

#endif // !NOVELRT_GRAPHICS_GRAPHICSMEMORYBLOCK_H
