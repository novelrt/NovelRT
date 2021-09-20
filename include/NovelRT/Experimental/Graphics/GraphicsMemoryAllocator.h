#include "TexelFormat.h"
#include <utility>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATOR_H
#define NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATOR_H

#ifndef NOVELRT_EXPERIMENTAL_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Experimental::Graphics
{
    class GraphicsMemoryAllocator : public GraphicsDeviceObject
    {
    protected:
        GraphicsMemoryAllocatorSettings _settings;

    public:
        GraphicsMemoryAllocator(std::shared_ptr<GraphicsDevice> device,
                                GraphicsMemoryAllocatorSettings settings) noexcept
            : GraphicsDeviceObject(std::move(device)), _settings(settings)
        {
            bool isExternallySynchronised =
                _settings.IsExternallySynchronised.has_value() && _settings.IsExternallySynchronised.value();

            int32_t maximumBlockCountPerCollection = _settings.MaximumBlockCountPerCollection > 0
                                                         ? _settings.MaximumBlockCountPerCollection
                                                         : std::numeric_limits<int32_t>::max();

            size_t maximumSharedBlockSize = _settings.MaximumSharedBlockSize.has_value()
                                                ? _settings.MaximumSharedBlockSize.value()
                                                : 256 * 1024 * 1024;

            int32_t minimumBlockCountPerCollection =
                _settings.MinimumBlockCountPerCollection >= 0 ? _settings.MinimumBlockCountPerCollection : 0;

            size_t minimumBlockSize = _settings.MinimumBlockSize != 0
                                          ? _settings.MinimumBlockSize
                                          : std::max(static_cast<size_t>(4096), maximumSharedBlockSize / 8);

            size_t minimumAllocatedRegionMarginSize = _settings.MinimumAllocatedRegionMarginSize.has_value()
                                                          ? _settings.MinimumAllocatedRegionMarginSize.value()
                                                          : 0;

            size_t minimumFreeRegionSizeToRegister =
                _settings.MinimumFreeRegionSizeToRegister != 0 ? _settings.MinimumFreeRegionSizeToRegister : 4096;

            _settings = GraphicsMemoryAllocatorSettings();
            _settings.IsExternallySynchronised = isExternallySynchronised;
            _settings.MaximumBlockCountPerCollection = maximumBlockCountPerCollection;
            _settings.MaximumSharedBlockSize = maximumSharedBlockSize;
            _settings.MinimumBlockCountPerCollection = minimumBlockCountPerCollection;
            _settings.MinimumBlockSize = minimumBlockSize;
            _settings.MinimumAllocatedRegionMarginSize = minimumAllocatedRegionMarginSize;
            _settings.MinimumFreeRegionSizeToRegister = minimumFreeRegionSizeToRegister;
        }

        [[nodiscard]] inline virtual int32_t GetCount() = 0;

        [[nodiscard]] inline const GraphicsMemoryAllocatorSettings& GetSettings() const noexcept
        {
            return _settings;
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsBuffer> CreateBuffer(
            GraphicsBufferKind bufferKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            size_t size,
            GraphicsMemoryRegionAllocationFlags allocationFlags) = 0;

        [[nodiscard]] std::shared_ptr<GraphicsBuffer> CreateBufferWithDefaultArguments(
            GraphicsBufferKind bufferKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            size_t size)
        {
            return CreateBuffer(bufferKind, cpuAccessKind, gpuAccessKind, size, GraphicsMemoryRegionAllocationFlags::None);
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsTexture> CreateTexture(
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width,
            uint32_t height,
            uint32_t depth,
            GraphicsMemoryRegionAllocationFlags allocationFlags,
            TexelFormat texelFormat) = 0;

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTextureWithDefaultArguments(
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width)
        {
            return CreateTextureWithDefaultArguments(textureKind, cpuAccessKind, gpuAccessKind, width, 1);
        }

        [[nodiscard]] std::shared_ptr<GraphicsTexture> CreateTextureWithDefaultArguments(
            GraphicsTextureKind textureKind,
            GraphicsResourceAccess cpuAccessKind,
            GraphicsResourceAccess gpuAccessKind,
            uint32_t width,
            uint32_t height)
        {
            return CreateTexture(textureKind, cpuAccessKind, gpuAccessKind, width, height, 1, GraphicsMemoryRegionAllocationFlags::None,
                                 TexelFormat::R8G8B8A8_UNORM);
        }

        [[nodiscard]] virtual GraphicsMemoryBudget GetBudget(
            std::shared_ptr<GraphicsMemoryBlockCollection> blockCollection) = 0;

        // TODO: maybe this should be std::list instead?
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator
        begin() = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator end() = 0;
    };

    template<typename TMetadata> class GraphicsMemoryAllocatorImpl : public GraphicsMemoryAllocator
    {
    public:
        using Metadata = TMetadata;

        GraphicsMemoryAllocatorImpl(std::shared_ptr<GraphicsDevice> device,
                                    GraphicsMemoryAllocatorSettings settings) noexcept
            : GraphicsMemoryAllocator(std::move(device), std::move(settings))
        {
            static_assert(
                std::is_base_of_v<IGraphicsMemoryRegionCollection<GraphicsResource>::IMetadata, TMetadata>);
        }
    };

} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATOR_H
