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

            size_t minimumBlockSize = _settings.MinimumBlockSize != 0 ? _settings.MinimumBlockSize
                                                                           : std::max(static_cast<size_t>(4096), maximumSharedBlockSize);

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

        [[nodiscard]] inline virtual int32_t GetCount() const noexcept = 0;

        [[nodiscard]] inline const GraphicsMemoryAllocatorSettings& GetSettings() const noexcept
        {
            return _settings;
        }

        [[nodiscard]] virtual std::shared_ptr<GraphicsTexture> CreateTexture(
            std::shared_ptr<IGraphicsMemoryRegionCollection<GraphicsResource>::IMetadata> metadata,
            GraphicsTextureKind textureKind,
            GraphicsResourceCpuAccessKind cpuAccessKind,
            size_t size,
            GraphicsMemoryRegionAllocationFlags allocationFlags = GraphicsMemoryRegionAllocationFlags::None) = 0;

        [[nodiscard]] virtual GraphicsMemoryBudget GetBudget(std::shared_ptr<GraphicsMemoryBlockCollection> blockCollection) = 0;

        // TODO: maybe this should be std::list instead?
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator
        begin() noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::const_iterator begin()
            const noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::const_iterator cbegin()
            const noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::iterator end() noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::const_iterator end()
            const noexcept = 0;
        [[nodiscard]] virtual std::vector<std::shared_ptr<GraphicsMemoryBlockCollection>>::const_iterator cend()
            const noexcept = 0;
    };
} // namespace NovelRT::Experimental::Graphics

#endif // !NOVELRT_EXPERIMENTAL_GRAPHICSMEMORYALLOCATOR_H
