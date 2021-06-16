#include <utility>

// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICSMEMORYALLOCATOR_H
#define NOVELRT_GRAPHICSMEMORYALLOCATOR_H

namespace NovelRT::Experimental::Graphics
{
    class GraphicsMemoryAllocator : public GraphicsDeviceObject
    {
    private:
        GraphicsMemoryAllocatorSettings _settings;

    public:
        GraphicsMemoryAllocator(std::shared_ptr<ILLGraphicsDevice> device,
                                GraphicsMemoryAllocatorSettings settings) noexcept
            : GraphicsDeviceObject(std::move(device)), _settings(settings)
        {
            bool isExternallySynchronised =
                _settings.IsExternallySynchronised.has_value() && _settings.IsExternallySynchronised.value();

            int32_t maximumBlockCountPerCollection = _settings.MaximumBlockCountPerCollection > 0
                                                         ? _settings.MaximumBlockCountPerCollection
                                                         : std::numeric_limits<int32_t>::max();

            uint64_t maximumSharedBlockSize = _settings.MaximumSharedBlockSize.has_value()
                                                  ? _settings.MaximumSharedBlockSize.value()
                                                  : 256ULL * 1024ULL * 1024ULL;

            int32_t minimumBlockCountPerCollection =
                _settings.MinimumBlockCountPerCollection >= 0 ? _settings.MinimumBlockCountPerCollection : 0;

            uint64_t minimumBlockSize = _settings.MinimumBlockSize != 0ULL ? _settings.MinimumBlockSize
                                                                           : std::max(4096ULL, maximumSharedBlockSize);

            uint64_t minimumAllocatedRegionMarginSize = _settings.MinimumAllocatedRegionMarginSize.has_value()
                                                            ? _settings.MinimumAllocatedRegionMarginSize.value()
                                                            : 0ULL;

            uint64_t minimumFreeRegionSizeToRegister =
                _settings.MinimumFreeRegionSizeToRegister != 0ULL ? _settings.MinimumFreeRegionSizeToRegister : 4096ULL;

            std::type_index regionCollectionMetadataType =
                _settings.RegionCollectionMetadataType.has_value()
                    ? _settings.RegionCollectionMetadataType.value()
                    : typeid(IGraphicsMemoryRegionCollection<GraphicsMemoryBlock>::DefaultMetadata);

            _settings = GraphicsMemoryAllocatorSettings();
            _settings.IsExternallySynchronised = isExternallySynchronised;
            _settings.MaximumBlockCountPerCollection = maximumBlockCountPerCollection;
            _settings.MaximumSharedBlockSize = maximumSharedBlockSize;
            _settings.MinimumBlockCountPerCollection = minimumBlockCountPerCollection;
            _settings.MinimumBlockSize = minimumBlockSize;
            _settings.MinimumAllocatedRegionMarginSize = minimumAllocatedRegionMarginSize;
            _settings.MinimumFreeRegionSizeToRegister = minimumFreeRegionSizeToRegister;
            _settings.RegionCollectionMetadataType = regionCollectionMetadataType;
        }

        [[nodiscard]] inline virtual int32_t GetCount() const noexcept = 0;

        [[nodiscard]] inline const GraphicsMemoryAllocatorSettings& GetSettings() const noexcept
        {
            return _settings;
        }

        [[nodiscard]] virtual std::shared_ptr<LLGraphicsTexture> CreateTexture(
            std::shared_ptr<IGraphicsMemoryRegionCollection<LLGraphicsResource>::IMetadata> metadata,
            GraphicsTextureKind textureKind,
            GraphicsResourceCpuAccessKind cpuAccessKind,
            size_t size,
            GraphicsMemoryRegionAllocationFlags allocationFlags = GraphicsMemoryRegionAllocationFlags::None) = 0;

        [[nodiscard]] virtual GraphicsMemoryBudget GetBudget(GraphicsMemoryBlockCollection blockCollection) = 0;

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

#endif // NOVELRT_GRAPHICSMEMORYALLOCATOR_H
