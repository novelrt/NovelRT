// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Experimental/Graphics/Graphics.h>

namespace NovelRT::Experimental::Graphics
{
    GraphicsMemoryBlock::GraphicsMemoryBlock(std::shared_ptr<GraphicsDevice> device,
                                             std::shared_ptr<GraphicsMemoryBlockCollection> collection)
        : GraphicsDeviceObject(std::move(device)), _collection(std::move(collection))
    {
        if (_collection == nullptr)
        {
            throw Exceptions::NullPointerException("Parameter: collection.");
        }

        // directly calling the base GetDevice here to avoid trouble with the virtual override.
        if (_collection->GetDevice() != GraphicsDeviceObject::GetDevice())
        {
            throw std::out_of_range("The same graphics device is not being used for this memory block. It is out "
                                    "of range of one of the devices.");
        }
    }
} // namespace NovelRT::Experimental::Graphics
