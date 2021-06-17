// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYBLOCKCOLLECTION_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYBLOCKCOLLECTION_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsMemoryBlockCollection : public GraphicsDeviceObject
    {
    private:
        std::shared_ptr<GraphicsMemoryAllocator> _allocator;
        std::vector<std::shared_ptr<GraphicsMemoryBlock>> _blocks;
        std::mutex _mutex;
        std::shared_ptr<GraphicsMemoryBlock> _emptyBlock;
        size_t _minimumSize;
        size_t _size;
        Threading::VolatileState _state;
    };
}

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYBLOCKCOLLECTION_H
