// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_GRAPHICS_IGRAPHICSMEMORYREGIONCOLLECTION_H
#define NOVELRT_GRAPHICS_IGRAPHICSMEMORYREGIONCOLLECTION_H

#ifndef NOVELRT_GRAPHICS_H
#error NovelRT does not support including types explicitly by default. Please include Graphics.h instead for the Graphics namespace subset.
#endif

namespace NovelRT::Graphics
{
    template<typename TSelf, typename TIterator = typename std::list<GraphicsMemoryRegion<TSelf>>::iterator>
    class IGraphicsMemoryRegionCollection
    {
    protected:
        [[nodiscard]] virtual GraphicsDevice* GetDeviceInternal() const noexcept = 0;

    public:
        IGraphicsMemoryRegionCollection() noexcept = default;
        IGraphicsMemoryRegionCollection(const IGraphicsMemoryRegionCollection<TSelf, TIterator>&) noexcept = delete;
        IGraphicsMemoryRegionCollection(IGraphicsMemoryRegionCollection<TSelf, TIterator>&&) noexcept = delete;
        IGraphicsMemoryRegionCollection<TSelf, TIterator>& operator=(
            const IGraphicsMemoryRegionCollection<TSelf, TIterator>&) noexcept = delete;
        IGraphicsMemoryRegionCollection<TSelf, TIterator>& operator=(
            IGraphicsMemoryRegionCollection<TSelf, TIterator>&&) noexcept = delete;
        virtual ~IGraphicsMemoryRegionCollection() = default;

        [[nodiscard]] virtual int32_t GetAllocatedRegionCount() = 0;

        [[nodiscard]] inline std::shared_ptr<GraphicsDevice> GetDevice() const noexcept
        {
            return GetDeviceInternal()->shared_from_this();
        }

        [[nodiscard]] virtual bool GetIsEmpty() = 0;
        [[nodiscard]] virtual size_t GetLargestFreeRegionSize() = 0;
        [[nodiscard]] virtual size_t GetMinimumAllocatedRegionMarginSize() = 0;
        [[nodiscard]] virtual size_t GetMinimumFreeRegionSizeToRegister() = 0;
        [[nodiscard]] virtual size_t GetSize() = 0;
        [[nodiscard]] virtual size_t GetTotalFreeRegionSize() = 0;
        [[nodiscard]] virtual GraphicsMemoryRegion<TSelf> Allocate(size_t size, size_t alignment) = 0;
        virtual void Clear() = 0;

        virtual void Free(const GraphicsMemoryRegion<TSelf>& region) = 0;

        [[nodiscard]] virtual bool TryAllocate(size_t size,
                                               size_t alignment,
                                               GraphicsMemoryRegion<TSelf>& outRegion) = 0;

        [[nodiscard]] GraphicsMemoryRegion<TSelf> Allocate(size_t size)
        {
            return Allocate(size, 1);
        }

        [[nodiscard]] bool TryAllocate(size_t size, GraphicsMemoryRegion<TSelf>& outRegion)
        {
            return TryAllocate(size, 1, outRegion);
        }

        [[nodiscard]] virtual TIterator begin() = 0;
        [[nodiscard]] virtual TIterator end() = 0;

        class IMetadata : public IGraphicsMemoryRegionCollection<TSelf, TIterator>
        {
        public:
            virtual void Initialise(std::shared_ptr<TSelf> collection,
                                    size_t size,
                                    size_t minimumAllocatedRegionMarginSize,
                                    size_t minimumFreeRegionSizeToRegister) = 0;

            IMetadata() noexcept = default;
            IMetadata(const IMetadata&) noexcept = delete;
            IMetadata(IMetadata&&) noexcept = delete;
            IMetadata& operator=(const IMetadata&) noexcept = delete;
            IMetadata& operator=(IMetadata&&) noexcept = delete;
            virtual ~IMetadata() = default;
        };

        class DefaultMetadata final : public IMetadata
        {
        private:
            std::shared_ptr<TSelf> _collection;
            std::shared_ptr<std::vector<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator>> _freeRegionsBySize;
            std::shared_ptr<std::list<GraphicsMemoryRegion<TSelf>>> _regions;
            size_t _minimumFreeRegionSizeToRegister;
            size_t _minimumAllocatedRegionMarginSize;
            size_t _size;
            size_t _totalFreeRegionSize;
            int32_t _freeRegionCount;
            std::shared_ptr<GraphicsDevice> _device;

        protected:
            [[nodiscard]] GraphicsDevice* GetDeviceInternal() const noexcept final
            {
                return _device.get();
            }

        public:
            explicit DefaultMetadata(std::shared_ptr<GraphicsDevice> device) noexcept
                : _collection(nullptr),
                  _freeRegionsBySize(
                      std::make_shared<std::vector<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator>>()),
                  _regions(std::make_shared<std::list<GraphicsMemoryRegion<TSelf>>>()),
                  _minimumFreeRegionSizeToRegister(static_cast<size_t>(-1)),
                  _minimumAllocatedRegionMarginSize(static_cast<size_t>(-1)),
                  _size(static_cast<size_t>(-1)),
                  _totalFreeRegionSize(static_cast<size_t>(-1)),
                  _freeRegionCount(-1),
                  _device(std::move(device))
            {
            }

            DefaultMetadata(const DefaultMetadata& other) noexcept
                : _collection(other._collection),
                  _freeRegionsBySize(other._freeRegionsBySize),
                  _regions(other._regions),
                  _minimumFreeRegionSizeToRegister(other._minimumFreeRegionSizeToRegister),
                  _minimumAllocatedRegionMarginSize(other._minimumAllocatedRegionMarginSize),
                  _size(other._size),
                  _totalFreeRegionSize(other._totalFreeRegionSize),
                  _freeRegionCount(other._freeRegionCount),
                  _device(other._device)
            {
            }

            DefaultMetadata(DefaultMetadata&& other) noexcept
                : _collection(std::move(other._collection)),
                  _freeRegionsBySize(std::move(other._freeRegionsBySize)),
                  _regions(std::move(other._regions)),
                  _minimumFreeRegionSizeToRegister(other._minimumFreeRegionSizeToRegister),
                  _minimumAllocatedRegionMarginSize(other._minimumAllocatedRegionMarginSize),
                  _size(other._size),
                  _totalFreeRegionSize(other._totalFreeRegionSize),
                  _freeRegionCount(other._freeRegionCount),
                  _device(std::move(other._device))
            {
                other._minimumFreeRegionSizeToRegister = static_cast<size_t>(-1);
                other._minimumAllocatedRegionMarginSize = static_cast<size_t>(-1);
                other._size = static_cast<size_t>(-1);
                other._totalFreeRegionSize = static_cast<size_t>(-1);
                other._freeRegionCount = -1;
            }

            DefaultMetadata& operator=(DefaultMetadata other) noexcept
            {
                std::swap(_collection, other._collection);
                std::swap(_freeRegionsBySize, other._freeRegionsBySize);
                std::swap(_regions, other._regions);
                std::swap(_minimumFreeRegionSizeToRegister, other._minimumFreeRegionSizeToRegister);
                std::swap(_minimumAllocatedRegionMarginSize, other._minimumAllocatedRegionMarginSize);
                std::swap(_size, other._size);
                std::swap(_totalFreeRegionSize, other._totalFreeRegionSize);
                std::swap(_freeRegionCount, other._freeRegionCount);
                std::swap(_device, other._device);

                return *this;
            }

            DefaultMetadata& operator=(DefaultMetadata&& other) noexcept
            {
                *this = std::move(other);
            }

            ~DefaultMetadata() final = default;

            [[nodiscard]] int32_t GetAllocatedRegionCount() final
            {
                return static_cast<int32_t>(_regions->size() - _freeRegionCount);
            }

            [[nodiscard]] size_t GetCount() const noexcept
            {
                return _regions->size();
            }

            [[nodiscard]] bool GetIsEmpty() final
            {
                return _regions->size() == 1 && _freeRegionCount == 1;
            }

            [[nodiscard]] size_t GetLargestFreeRegionSize() final
            {
                return _freeRegionsBySize->size() != 0 ? _freeRegionsBySize->back()->GetSize() : 0;
            }

            [[nodiscard]] size_t GetMinimumAllocatedRegionMarginSize() final
            {
                return _minimumAllocatedRegionMarginSize;
            }

            [[nodiscard]] size_t GetMinimumFreeRegionSizeToRegister() final
            {
                return _minimumFreeRegionSizeToRegister;
            }

            [[nodiscard]] size_t GetSize() final
            {
                return _size;
            }

            [[nodiscard]] size_t GetTotalFreeRegionSize() final
            {
                return _totalFreeRegionSize;
            }

            [[nodiscard]] GraphicsMemoryRegion<TSelf> Allocate(size_t size, size_t alignment) final
            {
                GraphicsMemoryRegion<TSelf> region(0, nullptr, nullptr, false, 0, 0);
                auto result = TryAllocate(size, alignment, region);

                if (!result)
                {
                    throw Exceptions::OutOfMemoryException("A size of " + std::to_string(result) +
                                                           " bytes was requested, but this size is too large.");
                }

                return region;
            }

            void Clear() final
            {
                size_t size = GetSize();

                _freeRegionCount = 1;
                _totalFreeRegionSize = size;

                _regions->clear();

                GraphicsMemoryRegion<TSelf> region(1, _collection, this->GetDevice(), false, 0, size);
                _regions->emplace_front(region);
                auto iterator = _regions->begin();
                _freeRegionsBySize->clear();
                _freeRegionsBySize->emplace_back(iterator);

                assert(Validate());
            }

            void Free(const GraphicsMemoryRegion<TSelf>& region) final
            {
                bool freedRegion = false;

                for (auto it = _regions->begin(); it != _regions->end(); std::advance(it, 1))
                {
                    if (*it != region)
                    {
                        continue;
                    }

                    static_cast<void>(FreeRegionInternal(it));
                    freedRegion = true;
                    break;
                }

                if (!freedRegion)
                {
                    throw Exceptions::KeyNotFoundException();
                }

                assert(Validate());
            }

            void Initialise(std::shared_ptr<TSelf> collection,
                            size_t size,
                            size_t minimumAllocatedRegionMarginSize,
                            size_t minimumFreeRegionSizeToRegister) final
            {
                if (collection == nullptr)
                {
                    throw Exceptions::NullPointerException("Parameter name: collection.");
                }

                if (size == 0)
                {
                    throw std::out_of_range(
                        "The size parameter was set to 0. This is not a valid size and is out of range.");
                }

                _collection = collection;
                _minimumAllocatedRegionMarginSize = minimumAllocatedRegionMarginSize;
                _minimumFreeRegionSizeToRegister = minimumFreeRegionSizeToRegister;
                _size = size;
                Clear();
            }

            [[nodiscard]] bool TryAllocate(size_t size, size_t alignment, GraphicsMemoryRegion<TSelf>& outRegion) final
            {
                if (size == 0)
                {
                    throw std::out_of_range(
                        "The size parameter was set to 0. This is not a valid size and is out of range.");
                }

                if (!Maths::Utilities::IsPow2(alignment))
                {
                    throw std::out_of_range("The provided alignment is invalid, as it is not to a power of two.");
                }

                size_t sizeWithMargins = size + (2 * GetMinimumAllocatedRegionMarginSize());
                bool allocatedRegion = false;

                if (GetTotalFreeRegionSize() >= sizeWithMargins)
                {
                    NovelRT::Utilities::Misc::Span<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator>
                        freeRegionsBySizeSpan(*_freeRegionsBySize);
                    size_t freeRegionsBySizeLength = freeRegionsBySizeSpan.size();

                    if (freeRegionsBySizeLength > 0)
                    {
                        for (auto index = BinarySearchFirstRegionNodeWithSizeNotLessThan(sizeWithMargins);
                             index < freeRegionsBySizeLength; ++index)
                        {
                            auto regionNode = freeRegionsBySizeSpan[index];

                            if (TryAllocateInternal(size, alignment, regionNode))
                            {
                                outRegion = *regionNode;
                                allocatedRegion = true;
                                break;
                            }
                        }
                    }
                }

                if (!allocatedRegion)
                {
                    outRegion = GraphicsMemoryRegion<TSelf>();
                }

                assert(Validate());

                return allocatedRegion;
            }

            [[nodiscard]] typename std::list<GraphicsMemoryRegion<TSelf>>::iterator begin() override
            {
                return _regions->begin();
            }

            [[nodiscard]] typename std::list<GraphicsMemoryRegion<TSelf>>::iterator end() override
            {
                return _regions->end();
            }

            /**
             * THIS IS ONLY USED BY DEBUG BUILDS
             */
            [[nodiscard]] bool Validate()
            {
                if (_regions->size() == 0)
                {
                    return false;
                }

                size_t calculatedSize = 0ULL;
                size_t calculatedTotalFreeRegionSize = 0ULL;

                int32_t calculatedFreeRegionCount = 0;
                size_t calculatedFreeRegionsToRegisterCount = 0;

                bool isPreviousRegionFree = false;

                for (auto&& region : *_regions)
                {
                    if (region.GetOffset() != calculatedSize)
                    {
                        return false;
                    }

                    bool isCurrentRegionFree = !region.GetIsAllocated();

                    if (isPreviousRegionFree && isCurrentRegionFree)
                    {
                        return false;
                    }

                    if (isCurrentRegionFree)
                    {
                        calculatedTotalFreeRegionSize += region.GetSize();
                        ++calculatedFreeRegionCount;

                        if (region.GetSize() >= GetMinimumFreeRegionSizeToRegister())
                        {
                            ++calculatedFreeRegionsToRegisterCount;
                        }

                        if (region.GetSize() < GetMinimumAllocatedRegionMarginSize())
                        {
                            return false;
                        }
                    }
                    else if (GetMinimumAllocatedRegionMarginSize() != 0 && !isPreviousRegionFree)
                    {
                        return false;
                    }

                    calculatedSize += region.GetSize();
                    isPreviousRegionFree = isCurrentRegionFree;
                }

                if (!ValidateFreeRegionsBySizeList())
                {
                    return false;
                }

                return calculatedSize == GetSize() && calculatedTotalFreeRegionSize == _totalFreeRegionSize &&
                       calculatedFreeRegionCount == _freeRegionCount &&
                       calculatedFreeRegionsToRegisterCount == _freeRegionsBySize->size();
            }

        private:
            [[nodiscard]] bool ValidateFreeRegionsBySizeList()
            {
                size_t lastRegionSize = 0ULL;

                for (auto&& region : *_freeRegionsBySize)
                {
                    if (region->GetIsAllocated() || region->GetSize() < GetMinimumFreeRegionSizeToRegister() ||
                        region->GetSize() < lastRegionSize)
                    {
                        return false;
                    }

                    lastRegionSize = region->GetSize();
                }

                return true;
            }

            [[nodiscard]] size_t BinarySearchFirstRegionNodeWithSizeNotLessThan(size_t size) const noexcept
            {
                NovelRT::Utilities::Misc::Span<const typename std::list<GraphicsMemoryRegion<TSelf>>::iterator>
                    freeRegionsBySizeSpan(&(*_freeRegionsBySize->begin()), _freeRegionsBySize->size());

                size_t index = 0;
                size_t endIndex = freeRegionsBySizeSpan.size();

                while (index < endIndex)
                {
                    size_t midIndex = (index + endIndex) / 2;

                    if (freeRegionsBySizeSpan[midIndex]->GetSize() < size)
                    {
                        index = midIndex + 1;
                    }
                    else
                    {
                        endIndex = midIndex;
                    }
                }

                return index;
            }

            [[nodiscard]] typename std::list<GraphicsMemoryRegion<TSelf>>::iterator FreeRegionInternal(
                typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                GraphicsMemoryRegion<TSelf>& region = *regionNode;

                if (!region.GetIsAllocated())
                {
                    return regionNode;
                }

                region = GraphicsMemoryRegion<TSelf>(region.GetAlignment(), region.GetCollection(), region.GetDevice(),
                                                     false, region.GetOffset(), region.GetSize());

                ++_freeRegionCount;
                _totalFreeRegionSize += region.GetSize();

                auto nextRegionNode = regionNode;
                std::advance(nextRegionNode, 1);
                bool mergeWithNext = nextRegionNode != _regions->end() && !nextRegionNode->GetIsAllocated();

                auto previousRegionNode = regionNode;
                std::advance(previousRegionNode, -1);
                bool mergeWithPrevious = previousRegionNode != _regions->end() && !previousRegionNode->GetIsAllocated();

                if (mergeWithNext)
                {
                    UnregisterFreeRegion(nextRegionNode);
                    MergeFreeRegionWithNext(regionNode);
                }

                if (mergeWithPrevious)
                {
                    UnregisterFreeRegion(previousRegionNode);
                    MergeFreeRegionWithNext(previousRegionNode);
                    RegisterFreeRegion(previousRegionNode);
                    return previousRegionNode;
                }
                else
                {
                    RegisterFreeRegion(regionNode);
                    return regionNode;
                }
            }

            void MergeFreeRegionWithNext(typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                auto nextRegionNode = regionNode;
                ++nextRegionNode;

                if (nextRegionNode->GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException(
                        "An allocated memory region was designated to be merged with an unallocated one.");
                }

                GraphicsMemoryRegion<TSelf>& region = *regionNode;
                const GraphicsMemoryRegion<TSelf>& nextRegion = *nextRegionNode;

                region = GraphicsMemoryRegion<TSelf>(region.GetAlignment(), region.GetCollection(), region.GetDevice(),
                                                     region.GetIsAllocated(), region.GetOffset(),
                                                     region.GetSize() + nextRegion.GetSize());

                --_freeRegionCount;

                _regions->erase(nextRegionNode);
            }

            void RegisterFreeRegion(typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                if (regionNode->GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException(
                        "An allocated memory region was designated to be registered as free.");
                }

                if (regionNode->GetSize() == 0)
                {
                    throw Exceptions::InvalidOperationException(
                        "A memory region of size 0 was provided as a free region to register.");
                }

                assert(ValidateFreeRegionsBySizeList());

                if (regionNode->GetSize() >= GetMinimumFreeRegionSizeToRegister())
                {
                    if (_freeRegionsBySize->size() == 0)
                    {
                        _freeRegionsBySize->emplace_back(regionNode);
                    }
                    else
                    {
                        size_t index = BinarySearchFirstRegionNodeWithSizeNotLessThan(regionNode->GetSize());
                        _freeRegionsBySize->insert(_freeRegionsBySize->begin() + index, regionNode);
                    }
                }

                assert(ValidateFreeRegionsBySizeList());
            }

            [[nodiscard]] bool TryAllocateInternal(size_t size,
                                                   size_t alignment,
                                                   typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                if (size <= 0)
                {
                    throw Exceptions::InvalidOperationException(
                        "An attempt to allocate a memory region of size 0 (or less) was made.");
                }

                if (regionNode == _collection->end())
                {
                    throw std::out_of_range("Parameter name: regionNode");
                }

                GraphicsMemoryRegion<TSelf>& region = *regionNode;

                if (region.GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException(
                        "An attempt to allocate a memory region that was already allocated was made.");
                }

                if (region.GetSize() < size)
                {
                    return false;
                }

                size_t offset = region.GetOffset();

                if (GetMinimumAllocatedRegionMarginSize() > 0)
                {
                    offset += GetMinimumAllocatedRegionMarginSize();
                }

                offset = Maths::Utilities::AlignUp(offset, alignment);
                size_t paddingBegin = offset - region.GetOffset();
                size_t requiredEndMargin = GetMinimumAllocatedRegionMarginSize();

                if ((paddingBegin + size + requiredEndMargin) > region.GetSize())
                {
                    return false;
                }

                size_t paddingEnd = region.GetSize() - paddingBegin - size;

                UnregisterFreeRegion(regionNode);

                region = GraphicsMemoryRegion<TSelf>(alignment, _collection, this->GetDevice(), true, offset, size);

                if (paddingEnd != 0)
                {
                    auto iterator = _regions->insert(std::next(regionNode),
                                                     GraphicsMemoryRegion<TSelf>(1, _collection, this->GetDevice(),
                                                                                 false, offset + size, paddingEnd));
                    RegisterFreeRegion(iterator);
                }

                if (paddingBegin != 0)
                {
                    auto iterator = _regions->insert(
                        regionNode, GraphicsMemoryRegion<TSelf>(1, _collection, this->GetDevice(), false,
                                                                offset - paddingBegin, paddingBegin));
                    RegisterFreeRegion(iterator);
                }

                --_freeRegionCount;

                if (paddingBegin > 0)
                {
                    ++_freeRegionCount;
                }

                if (paddingEnd > 0)
                {
                    ++_freeRegionCount;
                }

                _totalFreeRegionSize -= size;
                return true;
            }

            void UnregisterFreeRegion(typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                if (regionNode->GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException("An attempt was made to unregister a free region, but "
                                                                "the target region is currently allocated.");
                }

                if (regionNode->GetSize() <= 0)
                {
                    throw Exceptions::InvalidOperationException(
                        "An attempt was made to unregister an invalid region that has a size of 0 (or less).");
                }

                assert(ValidateFreeRegionsBySizeList());

                if (regionNode->GetSize() >= GetMinimumFreeRegionSizeToRegister())
                {
                    for (auto index = BinarySearchFirstRegionNodeWithSizeNotLessThan(regionNode->GetSize());
                         index < _freeRegionsBySize->size(); ++index)
                    {
                        if ((*_freeRegionsBySize)[index] == regionNode)
                        {
                            _freeRegionsBySize->erase(_freeRegionsBySize->begin() + index);
                            return;
                        }

                        if ((*_freeRegionsBySize)[index]->GetSize() != regionNode->GetSize())
                        {
                            // TODO: Fix exception message
                            throw std::runtime_error("Something broke lol");
                        }
                    }
                }

                assert(ValidateFreeRegionsBySizeList());
            }
        };
    };
}

#endif // NOVELRT_GRAPHICS_IGRAPHICSMEMORYREGIONCOLLECTION_H
