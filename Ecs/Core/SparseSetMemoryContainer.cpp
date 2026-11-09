// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/SparseSetMemoryContainer.hpp>
#include <NovelRT/Exceptions/DuplicateKeyException.hpp>
#include <NovelRT/Exceptions/InvalidOperationException.hpp>
#include <NovelRT/Exceptions/KeyNotFoundException.hpp>
#include <NovelRT/Utilities/Macros.hpp>
#include <NovelRT/Utilities/Memory.hpp>

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>

namespace NovelRT::Ecs
{
    SparseSetMemoryContainer::SparseSetMemoryContainer(size_t sizeOfDataTypeInBytes) noexcept
        : _dense{},
          _sparse{},
          _data{},
          _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes),
          _lastAccessedPagePtr(nullptr),
          _lastAccessedPageIndex(0ULL)
    {
    }

    size_t SparseSetMemoryContainer::GetStartingByteIndexForDenseIndex(size_t denseIndex) const noexcept
    {
        return _sizeOfDataTypeInBytes * denseIndex;
    }

    std::byte* SparseSetMemoryContainer::GetDataObjectStartAtIndex(size_t location) noexcept
    {
        return _data.data() + (location * _sizeOfDataTypeInBytes);
    }

    constexpr size_t SparseSetMemoryContainer::GetPageIndex(size_t key)
    {
        return key >> SparsePage::bitCount;
    }

    constexpr size_t SparseSetMemoryContainer::GetIndexInSparsePage(size_t key)
    {
        return key & SparsePage::entityIndexMask;
    }

    SparseSetMemoryContainer::SparsePage* SparseSetMemoryContainer::GetLastPageAccessedIfValid(
        size_t key) const noexcept
    {
        const size_t pageIndex = GetPageIndex(key);

        if (_lastAccessedPagePtr != nullptr && _lastAccessedPageIndex == pageIndex)
        {
            return _lastAccessedPagePtr;
        }

        return nullptr;
    }

    SparseSetMemoryContainer::SparsePage* SparseSetMemoryContainer::GetPageForKeyIfExists(size_t key) const noexcept
    {
        SparsePage* pagePtr = GetLastPageAccessedIfValid(key);

        if (pagePtr == nullptr && ContainsKey(key))
        {
            pagePtr = _sparse.at(GetPageIndex(key)).get();
        }

        return pagePtr;
    }

    void SparseSetMemoryContainer::InsertInternal(size_t key, const void* value)
    {
        // This is ignoring GetPageForKeyIfExists because in the event that
        // we need to actually create the page, we need to act on that information.
        // Best to just checked for cached and then do try_emplace.
        SparsePage* pagePtr = GetLastPageAccessedIfValid(key);

        const size_t pageIndex = GetPageIndex(key);
        bool newPageCreated = false;
        auto it = _sparse.end();

        if (pagePtr == nullptr)
        {
            const size_t minValue = SparsePage::size * pageIndex;
            const size_t maxValue =
                minValue + std::min(SparsePage::size - size_t(1), std::numeric_limits<size_t>::max() - minValue);

            auto [localIt, didInsert] = _sparse.try_emplace(
                pageIndex, std::make_unique<SparsePage>(
                               SparsePage{.data = {}, .minimumPageValue = minValue, .maximumPageValue = maxValue}));

            it = localIt;
            newPageCreated = didInsert;
            pagePtr = it->second.get();
        }

        const size_t originalDenseSize = _dense.size();
        const size_t originalDataSize = _data.size();

        if (originalDenseSize == _dense.max_size() ||
            (_sizeOfDataTypeInBytes != 0 && originalDenseSize + 1 > _data.max_size() / _sizeOfDataTypeInBytes))
        {
            throw std::length_error("The sparse set insertion exceeds storage capacity.");
        }

        const size_t requiredDataSize = GetStartingByteIndexForDenseIndex(originalDenseSize + 1);

        const auto ensureCapacity = [](auto& storage, size_t requiredCapacity)
        {
            if (requiredCapacity > storage.capacity())
            {
                const size_t grownCapacity =
                    storage.capacity() > storage.max_size() / 2 ? storage.max_size() : storage.capacity() * 2;
                storage.reserve(std::max(requiredCapacity, grownCapacity));
            }
        };

        ensureCapacity(_dense, originalDenseSize + 1ULL);
        ensureCapacity(_data, requiredDataSize);

        _dense.push_back(key);
        _data.resize(requiredDataSize);

        // TODO: Is this ever actually == 0? I feel like I should move this check. Assert maybe? - Matt J.

        if (_sizeOfDataTypeInBytes != 0)
        {
            const auto restoreInsertionState = [&]() noexcept
            {
                _data.resize(originalDataSize);
                _dense.resize(originalDenseSize);

                if (newPageCreated)
                {
                    _sparse.erase(it);
                }
            };

            try
            {
                NovelRT::Utilities::Memory::Copy(
                    NovelRT::Utilities::Span<const std::byte>{static_cast<const std::byte*>(value),
                                                              _sizeOfDataTypeInBytes},
                    NovelRT::Utilities::Span<std::byte>{GetDataObjectStartAtIndex(originalDenseSize),
                                                        _sizeOfDataTypeInBytes});
            }
            catch (const Exceptions::InvalidOperationException&)
            {
                restoreInsertionState();
                throw;
            }
            catch (const std::bad_alloc&)
            {
                restoreInsertionState();
                throw;
            }
        }

        // we now add 1 here because 0 is a sentinel value. We account for this elsewhere.
        // Yes I know it's brittle but I literally could not think of another way to do this
        // right now that I didn't completely despise. - Matt J.

        pagePtr->data[GetIndexInSparsePage(key)] = originalDenseSize + 1;

        _lastAccessedPageIndex = pageIndex;
        _lastAccessedPagePtr = pagePtr;
    }

    void SparseSetMemoryContainer::Insert(size_t key, const void* value)
    {
        if (ContainsKey(key))
        {
            throw Exceptions::DuplicateKeyException();
        }

        InsertInternal(key, value);
    }

    SparseSetInsertResult SparseSetMemoryContainer::TryInsert(size_t key, const void* value) noexcept
    {
        if (ContainsKey(key))
        {
            return SparseSetInsertResult::AlreadyExists;
        }

        try
        {
            InsertInternal(key, value);
            return SparseSetInsertResult::Inserted;
        }
        catch (const std::bad_alloc&)
        {
            return SparseSetInsertResult::AllocationFailed;
        }
        catch (const Exceptions::InvalidOperationException&)
        {
            return SparseSetInsertResult::CopyValidationFailed;
        }
        catch (...)
        {
            return SparseSetInsertResult::UnknownFailure;
        }
    }

    void SparseSetMemoryContainer::Remove(size_t key)
    {
        SparsePage* pagePtr = GetPageForKeyIfExists(key);

        if (pagePtr == nullptr)
        {
            throw Exceptions::KeyNotFoundException();
        }

        std::array<size_t, SparsePage::size>& pageData = pagePtr->data;
        const size_t pageOffset = key - pagePtr->minimumPageValue;
        const size_t denseIndex = pageData[pageOffset] - 1ULL;

        auto byteIndex = GetStartingByteIndexForDenseIndex(denseIndex);

        pageData[pageOffset] = 0ULL;

        if (std::ranges::all_of(pageData, [](size_t x) { return x == 0; }))
        {
            _sparse.erase(GetPageIndex(key));
            _lastAccessedPagePtr = nullptr;
            _lastAccessedPageIndex = 0ULL;
        }

        // reworked the insane data aligning/ordering logic from the first implementation of this to be easier to
        // maintain now we have pages. I was definitely a bit stupid when I wrote this the first time. - Matt J.

        _dense.erase(_dense.begin() + static_cast<std::vector<size_t>::difference_type>(denseIndex));

        _data.erase(_data.begin() + std::vector<std::byte>::difference_type(byteIndex),
                    _data.begin() + std::vector<std::byte>::difference_type(byteIndex + _sizeOfDataTypeInBytes));

        const size_t removedStoredIndex = denseIndex + 1;

        for (auto& [key, page] : _sparse)
        {
            for (size_t& storedIndex : page->data)
            {
                if (storedIndex > removedStoredIndex)
                {
                    --storedIndex;
                }
            }
        }
    }

    bool SparseSetMemoryContainer::TryRemove(size_t key) noexcept
    {
        if (!ContainsKey(key))
        {
            return false;
        }

        try
        {
            Remove(key);
            return true;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    void SparseSetMemoryContainer::Clear() noexcept
    {
        _dense.clear();
        _sparse.clear();
        _data.clear();
        _lastAccessedPageIndex = 0ULL;
        _lastAccessedPagePtr = nullptr;
    }

    bool SparseSetMemoryContainer::ContainsKey(size_t key) const noexcept
    {
        const size_t pageIndex = GetPageIndex(key);
        const size_t keyIndex = GetIndexInSparsePage(key);

        const auto it = _sparse.find(pageIndex);

        return it != _sparse.end() && it->second->data[keyIndex] != 0ULL;
    }

    size_t SparseSetMemoryContainer::GetDenseIndex(size_t key) const
    {
        if (!ContainsKey(key))
        {
            throw Exceptions::KeyNotFoundException();
        }

        SparsePage* pagePtr = GetLastPageAccessedIfValid(key);

        if (pagePtr == nullptr)
        {
            pagePtr = _sparse.at(GetPageIndex(key)).get();
        }

        const auto& pageData = pagePtr->data;

        return pageData[GetIndexInSparsePage(key)] - 1ULL;
    }

    size_t SparseSetMemoryContainer::CopyKeyBasedOnDenseIndex(size_t denseIndex) const
    {
        return _dense.at(denseIndex);
    }

    size_t SparseSetMemoryContainer::CopyKeyBasedOnDenseIndexUnsafe(size_t denseIndex) const noexcept
    {
        return _dense[denseIndex];
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::GetByteIteratorViewBasedOnDenseIndex(
        size_t denseIndex)
    {
        if (denseIndex >= Length())
        {
            throw std::out_of_range("denseIndex exceeds the range of the dense data.");
        }

        return SparseSetMemoryContainer::ByteIteratorView(
            _data.begin() + std::vector<std::byte>::difference_type(GetStartingByteIndexForDenseIndex(denseIndex)),
            _sizeOfDataTypeInBytes);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::GetByteIteratorViewBasedOnDenseIndex(
        size_t denseIndex) const
    {
        if (denseIndex >= Length())
        {
            throw std::out_of_range("denseIndex exceeds the range of the dense data.");
        }

        return SparseSetMemoryContainer::ConstByteIteratorView(
            _data.cbegin() + std::vector<std::byte>::difference_type(GetStartingByteIndexForDenseIndex(denseIndex)),
            _sizeOfDataTypeInBytes);
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::GetByteIteratorViewBasedOnDenseIndexUnsafe(
        size_t denseIndex) noexcept
    {
        return SparseSetMemoryContainer::ByteIteratorView(
            _data.begin() + std::vector<std::byte>::difference_type(GetStartingByteIndexForDenseIndex(denseIndex)),
            _sizeOfDataTypeInBytes);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::
        GetByteIteratorViewBasedOnDenseIndexUnsafe(size_t denseIndex) const noexcept
    {
        return SparseSetMemoryContainer::ConstByteIteratorView(
            _data.cbegin() + std::vector<std::byte>::difference_type(GetStartingByteIndexForDenseIndex(denseIndex)),
            _sizeOfDataTypeInBytes);
    }

    size_t SparseSetMemoryContainer::Length() const noexcept
    {
        return _dense.size();
    }

    void SparseSetMemoryContainer::ResetAndWriteDenseData(NovelRT::Utilities::Span<const size_t> keys,
                                                          NovelRT::Utilities::Span<const std::byte> data)
    {
        _lastAccessedPageIndex = 0ULL;
        _lastAccessedPagePtr = nullptr;
        _dense.clear();
        _dense.reserve(keys.size());
        _sparse.clear();
        _data.clear();

        for (size_t key : keys)
        {
            SparsePage* pagePtr = GetPageForKeyIfExists(key);

            if (pagePtr == nullptr)
            {
                const size_t pageIndex = GetPageIndex(key);
                const size_t minValue = SparsePage::size * pageIndex;
                const size_t maxValue =
                    minValue + std::min(SparsePage::size - size_t(1), std::numeric_limits<size_t>::max() - minValue);

                auto [it, _] = _sparse.emplace(
                    pageIndex, std::make_unique<SparsePage>(
                                   SparsePage{.data = {}, .minimumPageValue = minValue, .maximumPageValue = maxValue}));

                pagePtr = it->second.get();
            }

            _dense.push_back(key);

            // Accounting for the sentinel value with the removal of the -1. - Matt J.
            pagePtr->data[GetIndexInSparsePage(key)] = _dense.size();
        }

        _data.resize(data.size());
        NovelRT::Utilities::Memory::Copy(data, {_data});
    }

    void SparseSetMemoryContainer::ResetAndWriteDenseData(const size_t* ids, size_t length, const std::byte* data)
    {
        ResetAndWriteDenseData({ids, length}, {data, length * GetSizeOfDataTypeInBytes()});
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::operator[](size_t key) noexcept
    {
        SparsePage* pagePtr = GetPageForKeyIfExists(key);

        return GetByteIteratorViewBasedOnDenseIndexUnsafe(pagePtr->data[key - pagePtr->minimumPageValue] - 1ULL);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::operator[](size_t key) const noexcept
    {
        SparsePage* pagePtr = GetPageForKeyIfExists(key);

        return GetByteIteratorViewBasedOnDenseIndexUnsafe(pagePtr->data[key - pagePtr->minimumPageValue] - 1ULL);
    }

    SparseSetMemoryContainer::Iterator SparseSetMemoryContainer::begin() noexcept
    {
        return SparseSetMemoryContainer::Iterator(
            std::make_tuple(_dense.begin(), ByteIteratorView(_data.begin(), _sizeOfDataTypeInBytes)));
    }

    SparseSetMemoryContainer::Iterator SparseSetMemoryContainer::end() noexcept
    {
        return SparseSetMemoryContainer::Iterator(std::make_tuple(_dense.end(), ByteIteratorView(_data.end(), 0)));
    }

    SparseSetMemoryContainer::ConstIterator SparseSetMemoryContainer::begin() const noexcept
    {
        return cbegin();
    }

    SparseSetMemoryContainer::ConstIterator SparseSetMemoryContainer::end() const noexcept
    {
        return cend();
    }

    SparseSetMemoryContainer::ConstIterator SparseSetMemoryContainer::cbegin() const noexcept
    {
        return SparseSetMemoryContainer::ConstIterator(
            std::make_tuple(_dense.cbegin(), ConstByteIteratorView(_data.cbegin(), _sizeOfDataTypeInBytes)));
    }

    SparseSetMemoryContainer::ConstIterator SparseSetMemoryContainer::cend() const noexcept
    {
        return SparseSetMemoryContainer::ConstIterator(
            std::make_tuple(_dense.cend(), ConstByteIteratorView(_data.cend(), 0)));
    }
} // namespace NovelRT::Ecs
