// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_IGRAPHICSMEMORYREGIONCOLLECTION_H
#define NOVELRT_IGRAPHICSMEMORYREGIONCOLLECTION_H

namespace NovelRT::Experimental::Graphics
{
    template<typename TCollection> class GraphicsMemoryRegion
    {
    private:
        size_t _alignment;
        std::shared_ptr<TCollection> _collection;
        std::shared_ptr<ILLGraphicsDevice> _device;
        bool _isAllocated;
        size_t _offset;
        size_t _size;

    public:
        GraphicsMemoryRegion(size_t alignment,
                             std::shared_ptr<TCollection> collection,
                             std::shared_ptr<ILLGraphicsDevice> device,
                             bool isAllocated,
                             size_t offset,
                             size_t size) noexcept
            : _alignment(alignment),
              _collection(std::move(collection)),
              _device(std::move(device)),
              _isAllocated(isAllocated),
              _offset(offset),
              _size(size)
        {
        }

        [[nodiscard]] size_t GetAlignment() const noexcept
        {
            return _alignment;
        }

        [[nodiscard]] std::shared_ptr<TCollection> GetCollection() const noexcept
        {
            return _collection;
        }

        [[nodiscard]] std::shared_ptr<ILLGraphicsDevice> GetDevice() const noexcept
        {
            return _device;
        }

        [[nodiscard]] bool GetIsAllocated() const noexcept
        {
            return _isAllocated;
        }

        [[nodiscard]] size_t GetOffset() const noexcept
        {
            return _offset;
        }

        [[nodiscard]] size_t GetSize() const noexcept
        {
            return _size;
        }

        [[nodiscard]] bool operator==(const GraphicsMemoryRegion<TCollection>& rhs) const noexcept
        {
            return (GetCollection() == rhs.GetCollection()) && (GetIsAllocated() == rhs.GetIsAllocated()) &&
                   (GetOffset() == rhs.GetOffset()) && (GetSize() == rhs.GetSize()) &&
                   (GetAlignment() == rhs.GetAlignment());
        }

        [[nodiscard]] bool operator!=(const GraphicsMemoryRegion<TCollection>& rhs) const noexcept
        {
            return !(*this == rhs);
        }
    };

    template<typename TSelf, typename TIterator> class IGraphicsMemoryRegionCollection
    {
    public:
        [[nodiscard]] virtual int32_t GetAllocatedRegionCount() const noexcept = 0;
        [[nodiscard]] virtual std::shared_ptr<ILLGraphicsDevice> GetDevice() const noexcept = 0;
        [[nodiscard]] virtual bool GetIsEmpty() const noexcept = 0;
        [[nodiscard]] virtual size_t GetLargestFreeRegionSize() const noexcept = 0;
        [[nodiscard]] virtual size_t GetMinimumAllocatedRegionMarginSize() const noexcept = 0;
        [[nodiscard]] virtual size_t GetMinimumFreeRegionSizeToRegister() const noexcept = 0;
        [[nodiscard]] virtual size_t GetSize() const noexcept = 0;
        [[nodiscard]] virtual size_t GetTotalFreeRegionSize() const noexcept = 0;
        [[nodiscard]] virtual GraphicsMemoryRegion<TSelf> Allocate(size_t size, size_t alignment) = 0;
        virtual void Clear() = 0;

        virtual void Free(GraphicsMemoryRegion<TSelf> region) = 0;

        [[nodiscard]] virtual bool TryAllocate(size_t size,
                                               size_t alignment,
                                               GraphicsMemoryRegion<TSelf>& outRegion) = 0;

        [[nodiscard]] GraphicsMemoryRegion<TSelf> Allocate(size_t size)
        {
            return std::move(Allocate(size, 1ULL));
        }

        [[nodiscard]] bool TryAllocate(size_t size, GraphicsMemoryRegion<TSelf>& outRegion)
        {
            return TryAllocate(size, 1ULL, outRegion);
        }

        virtual [[nodiscard]] TIterator begin() = 0;
        virtual [[nodiscard]] TIterator end() = 0;

        class IMetadata
            : public IGraphicsMemoryRegionCollection<TSelf, TIterator>
        {
        public:
            virtual void Initialise(std::shared_ptr<TSelf> collection,
                                    size_t size,
                                    size_t minimumAllocatedRegionMarginSize,
                                    size_t minimumFreeRegionSizeToRegister) = 0;
        };

        class DefaultMetadata : public IMetadata
        {
        private:
            std::shared_ptr<TSelf> _collection;
            std::vector<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator> _freeRegionsBySize;
            std::list<GraphicsMemoryRegion<TSelf>> _regions;
            size_t _minimumFreeRegionSizeToRegister;
            size_t _minimumAllocatedRegionMarginSize;
            size_t _size;
            size_t _totalFreeRegionSize;
            int32_t _freeRegionCount;

        public:
            DefaultMetadata() noexcept
                : _collection(nullptr),
                  _freeRegionsBySize(std::vector<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator>{}),
                  _regions(std::list<GraphicsMemoryRegion<TSelf>>{}),
                  _minimumFreeRegionSizeToRegister(-1ULL),
                  _minimumAllocatedRegionMarginSize(-1ULL),
                  _size(-1ULL),
                  _totalFreeRegionSize(-1ULL),
                  _freeRegionCount(-1)
            {
            }

            [[nodiscard]] int32_t GetAllocatedRegionCount() const noexcept final
            {
                return _regions.size() - _freeRegionCount;
            }

            [[nodiscard]] std::shared_ptr<ILLGraphicsDevice> GetDevice() const noexcept final
            {
                return _collection->GetDevice();
            }

            [[nodiscard]] bool GetIsEmpty() const noexcept override
            {
                return _regions.size() == 1 && _freeRegionCount == 1;
            }

            [[nodiscard]] size_t GetLargestFreeRegionSize() const noexcept final
            {
                return _freeRegionsBySize.size() != 0ULL ? _freeRegionsBySize.back().GetSize() : 0ULL;
            }

            [[nodiscard]] size_t GetMinimumAllocatedRegionMarginSize() const noexcept final
            {
                return _minimumAllocatedRegionMarginSize;
            }

            [[nodiscard]] size_t GetMinimumFreeRegionSizeToRegister() const noexcept final
            {
                return _minimumFreeRegionSizeToRegister;
            }

            [[nodiscard]] size_t GetSize() const noexcept final
            {
                return _size;
            }

            [[nodiscard]] size_t GetTotalFreeRegionSize() const noexcept final
            {
                return _totalFreeRegionSize;
            }

            [[nodiscard]] GraphicsMemoryRegion<TSelf> Allocate(size_t size, size_t alignment) final
            {
                GraphicsMemoryRegion<TSelf> region = nullptr;
                auto result = TryAllocate(size, alignment, region);

                if (!result)
                {
                    // TODO: figure out how to return the size...?
                    throw Exceptions::OutOfMemoryException();
                }

                return std::move(region);
            }

            void Clear() final
            {
                size_t size = GetSize();

                _freeRegionCount = 1;
                _totalFreeRegionSize = size;

                _regions.clear();

                GraphicsMemoryRegion<TSelf> region(1, _collection, false, 0ULL, size);
                auto iterator = _regions.emplace_front(region);
                _freeRegionsBySize.clear();
                _freeRegionsBySize.emplace_back(iterator);

                // TODO: implement debug validation here?
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

                if (size == 0ULL)
                {
                    throw std::out_of_range(
                        "The size parameter was set to 0. This is not a valid size and is out of range.");
                }

                _minimumAllocatedRegionMarginSize = minimumAllocatedRegionMarginSize;
                _minimumFreeRegionSizeToRegister = minimumFreeRegionSizeToRegister;
                _size = size;
                Clear();
            }

            [[nodiscard]] bool TryAllocate(size_t size, size_t alignment, GraphicsMemoryRegion<TSelf>& outRegion) final
            {
                if (size == 0ULL)
                {
                    throw std::out_of_range(
                        "The size parameter was set to 0. This is not a valid size and is out of range.");
                }

                if ((alignment & (alignment - 1)) != 0)
                {
                    throw std::out_of_range("The provided alignment is invalid, as it is not to a power of two.");
                }

                size_t sizeWithMargins = size + (2 * GetMinimumAllocatedRegionMarginSize());
                bool allocatedRegion = false;

                if (GetTotalFreeRegionSize() >= sizeWithMargins)
                {
                    gsl::span<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator> freeRegionsBySizeSpan(
                        _freeRegionsBySize);
                    size_t freeRegionsBySizeLength = freeRegionsBySizeSpan.size();

                    if (freeRegionsBySizeSpan > 0)
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

                return allocatedRegion;
            }

        private:
            [[nodiscard]] size_t BinarySearchFirstRegionNodeWithSizeNotLessThan(size_t size) const noexcept
            {
                gsl::span<typename std::list<GraphicsMemoryRegion<TSelf>>::iterator> freeRegionsBySizeSpan(
                    _freeRegionsBySize);

                size_t index = 0ULL;
                size_t endIndex = freeRegionsBySizeSpan.size();

                while (index < endIndex)
                {
                    size_t midIndex = (index + endIndex) / 2ULL;

                    if (freeRegionsBySizeSpan[midIndex]->GetSize() < size)
                    {
                        index = midIndex + 1ULL;
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

                if (!region->GetIsAllocated())
                {
                    return regionNode;
                }

                *region = GraphicsMemoryRegion<TSelf>(region->GetAlignment(), region->GetCollection(), false,
                                                      region->GetOffset(), region->GetSize());

                ++_freeRegionCount;
                _totalFreeRegionSize += region->GetSize();

                auto nextRegionNode = regionNode;
                ++nextRegionNode;
                bool mergeWithNext = *nextRegionNode != nullptr && !nextRegionNode->GetIsAllocated();

                auto previousRegionNode = regionNode;
                ++previousRegionNode;
                bool mergeWithPrevious = *previousRegionNode != nullptr && !previousRegionNode->GetIsAllocated();

                if (mergeWithNext)
                {
                    // TODO: I suck at translating assertions.
                    if (*nextRegionNode == nullptr)
                    {
                        throw Exceptions::NullPointerException("A memory region node is nullptr.");
                    }

                    UnregisterFreeRegion(nextRegionNode);
                    MergeFreeRegionWithNext(regionNode);
                }

                if (mergeWithPrevious)
                {
                    // TODO: I suck at translating assertions.
                    if (*nextRegionNode == nullptr)
                    {
                        throw Exceptions::NullPointerException("A memory region node is nullptr.");
                    }

                    UnregisterFreeRegion(previousRegionNode);
                    MergeFreeRegionWithNext(previousRegionNode);
                    RegisterFreeRegion(previousRegionNode);
                }
                else
                {
                    RegisterFreeRegion(regionNode);
                    return regionNode;
                }
            }

            void MergeFreeRegionWithNext(typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                if (*regionNode == nullptr)
                {
                    throw Exceptions::NullPointerException("A memory region node is nullptr.");
                }

                auto nextRegionNode = regionNode;
                ++nextRegionNode;

                if (*nextRegionNode == nullptr)
                {
                    throw Exceptions::NullPointerException("A memory region node is nullptr.");
                }

                if (nextRegionNode->GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException(
                        "An allocated memory region was designated to be merged with an unallocated one.");
                }

                GraphicsMemoryRegion<TSelf>& region = *regionNode;
                const GraphicsMemoryRegion<TSelf>& nextRegion = *nextRegionNode;

                *region = GraphicsMemoryRegion<TSelf>(region->GetAlignment(), region->GetCollection(),
                                                      region->GetIsAllocated(), region->GetOffset(),
                                                      region->GetSize() + nextRegion->GetSize());

                --_freeRegionCount;

                _regions.erase(nextRegionNode);
            }

            void RegisterFreeRegion(typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                if (regionNode->GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException(
                        "An allocated memory region was designated to be registered as free.");
                }

                // TODO: this is unsigned. I probably can get away with == but whatever.
                if (regionNode->GetSize() <= 0ULL)
                {
                    throw Exceptions::InvalidOperationException(
                        "A memory region of size 0 (or less) was provided as a free region to register.");
                }

                // TODO: validate free regions by size list

                if (regionNode->GetSize() >= GetMinimumFreeRegionSizeToRegister())
                {
                    if (_freeRegionsBySize.size() == 0ULL)
                    {
                        _freeRegionsBySize.emplace_back(regionNode);
                    }
                    else
                    {
                        size_t index = BinarySearchFirstRegionNodeWithSizeNotLessThan(regionNode->GetSize());
                        _freeRegionsBySize.insert(_freeRegionsBySize.begin() + index, regionNode);
                    }
                }

                // TODO: validate free regions by size list
            }

            [[nodiscard]] bool TryAllocateInternal(size_t size,
                                                   size_t alignment,
                                                   typename std::list<GraphicsMemoryRegion<TSelf>>::iterator regionNode)
            {
                if (size <= 0ULL)
                {
                    throw Exceptions::InvalidOperationException(
                        "An attempt to allocate a memory region of size 0 (or less) was made.");
                }

                if (*regionNode == nullptr)
                {
                    throw Exceptions::NullPointerException("Parameter name: regionNode");
                }

                GraphicsMemoryRegion<TSelf>& region = *regionNode;

                if (region->GetIsAllocated())
                {
                    throw Exceptions::InvalidOperationException(
                        "An attempt to allocate a memory region that was already allocated was made.");
                }

                if (region->GetSize() < size)
                {
                    return false;
                }

                size_t offset = region->GetOffset();

                if (GetMinimumAllocatedRegionMarginSize() > 0ULL)
                {
                    offset += GetMinimumAllocatedRegionMarginSize();
                }

                offset = Maths::Utilities::AlignUp(offset, alignment);
                size_t paddingBegin = offset - region->GetOffset();
                size_t requiredEndMargin = GetMinimumAllocatedRegionMarginSize();

                if ((paddingBegin + size + requiredEndMargin) > size)
                {
                    return false;
                }

                size_t paddingEnd = region->GetSize() - paddingBegin - size;

                UnregisterFreeRegion(regionNode);

                *region = GraphicsMemoryRegion<TSelf>(alignment, _collection, true, offset, size);

                if (paddingEnd != 0)
                {
                    auto iterator = _regions.insert(std::next(regionNode),
                                                    std::make_shared<GraphicsMemoryRegion<TSelf>>(
                                                        1ULL, _collection, false, offset + size, paddingEnd));
                    RegisterFreeRegion(iterator);
                }

                if (paddingBegin != 0)
                {
                    auto iterator =
                        _regions.insert(regionNode, std::make_shared<GraphicsMemoryRegion<TSelf>>(
                                                        1ULL, _collection, false, offset - paddingBegin, paddingBegin));
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

                if (regionNode->GetSize() <= 0ULL)
                {
                    throw Exceptions::InvalidOperationException(
                        "An attempt was made to unregister an invalid region that has a size of 0 (or less).");
                }

                // TODO: validate free regions by size list

                if (regionNode->GetSize() >= GetMinimumFreeRegionSizeToRegister())
                {
                    for (auto index = BinarySearchFirstRegionNodeWithSizeNotLessThan(regionNode->GetSize());
                         index < _freeRegionsBySize.size(); ++index)
                    {
                        if (_freeRegionsBySize[index] == regionNode)
                        {
                            _freeRegionsBySize.erase(_freeRegionsBySize.begin() + index);
                            return;
                        }

                        if (_freeRegionsBySize[index]->GetSize() != regionNode->GetSize())
                        {
                            // TODO: Fix exception message
                            throw std::runtime_error("Something broke lol");
                        }
                    }
                }

                // TODO: Validate free regions by size list
            }

            [[nodiscard]] typename std::list<GraphicsMemoryRegion<TSelf>>::iterator begin() override
            {
                return _regions.begin();
            }

            [[nodiscard]] typename std::list<GraphicsMemoryRegion<TSelf>>::iterator end() override
            {
                return _regions.end();
            }
        };
    };
} // namespace NovelRT::Experimental::Graphics

#endif // NOVELRT_IGRAPHICSMEMORYREGIONCOLLECTION_H
