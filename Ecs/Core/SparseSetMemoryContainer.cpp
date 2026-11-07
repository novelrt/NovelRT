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
        : _dense(), _sparse(), _data(), _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes)
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

    void SparseSetMemoryContainer::InsertInternal(size_t key, const void* value)
    {
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse.begin(), _sparse.end(), [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        bool newPageCreated = false;

        if (it == _sparse.end())
        {
            newPageCreated = true;

            const size_t pageIndex = key / SparsePage::size;
            const size_t minValue = SparsePage::size * pageIndex;
            const size_t maxValue =
                minValue + std::min(SparsePage::size - size_t(1), std::numeric_limits<size_t>::max() - minValue);

            _sparse.emplace_back(std::make_unique<SparsePage>(SparsePage{.data = std::vector<size_t>(SparsePage::size),
                                                                         .minimumPageValue = minValue,
                                                                         .maximumPageValue = maxValue}));

            it = std::prev(_sparse.end());
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

        // not inlined into the indexer because I don't hate myself. - Matt J.
        const size_t pageOffset = key - (*it)->minimumPageValue;

        // we now add 1 here because 0 is a sentinel value. We account for this elsewhere.
        // Yes I know it's brittle but I literally could not think of another way to do this
        // right now that I didn't completely despise. - Matt J.
        (*it)->data[pageOffset] = originalDenseSize + 1;

        std::ranges::sort(_sparse, [](const auto& lhs, const auto& rhs)
                          { return lhs->maximumPageValue < rhs->minimumPageValue; });
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
        if (!ContainsKey(key))
        {
            throw Exceptions::KeyNotFoundException();
        }

        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target. THIS SHOULD ALWAYS BE VALID HERE because of the ContainsKey call.
        auto it = std::ranges::find_if(
            _sparse.begin(), _sparse.end(), [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        std::vector<size_t>& pageData = (*it)->data;
        const size_t pageOffset = key - (*it)->minimumPageValue;
        const size_t denseIndex = pageData[pageOffset] - 1ULL;

        auto byteIndex = GetStartingByteIndexForDenseIndex(denseIndex);

        pageData[pageOffset] = 0ULL;

        if (std::ranges::all_of(pageData, [](size_t x) { return x == 0; }))
        {
            _sparse.erase(it);
        }

        // reworked the insane data aligning/ordering logic from the first implementation of this to be easier to
        // maintain now we have pages. I was definitely a bit stupid when I wrote this the first time. - Matt J.

        _dense.erase(_dense.begin() + static_cast<std::vector<size_t>::difference_type>(denseIndex));

        _data.erase(_data.begin() + std::vector<std::byte>::difference_type(byteIndex),
                    _data.begin() + std::vector<std::byte>::difference_type(byteIndex + _sizeOfDataTypeInBytes));

        const size_t removedStoredIndex = denseIndex + 1;

        for (std::unique_ptr<SparsePage>& page : _sparse)
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
    }

    bool SparseSetMemoryContainer::ContainsKey(size_t key) const noexcept
    {
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target. Not sure if there's a way to do that? - Matt J.
        auto it = std::ranges::find_if(
            _sparse.begin(), _sparse.end(), [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        if (it == _sparse.end())
        {
            return false;
        }

        const size_t pageOffset = key - (*it)->minimumPageValue;
        const std::vector<size_t>& pageData = (*it)->data;

        // Would need to elminate the variable below to inline this as part of the return value. Cursed. - Matt J.
        if (pageOffset >= pageData.size() || pageData[pageOffset] == 0)
        {
            return false;
        }

        const size_t denseIndex = pageData[pageOffset] - 1;

        return denseIndex < _dense.size() && _dense[denseIndex] == key;
    }

    size_t SparseSetMemoryContainer::GetDenseIndex(size_t key) const
    {
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse.begin(), _sparse.end(), [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        // Have to separate these for memory safety. Ew. - Matt J.
        if (it == _sparse.end())
        {
            throw Exceptions::KeyNotFoundException();
        }

        const size_t pageOffset = key - (*it)->minimumPageValue;
        const auto& pageData = (*it)->data;

        if (pageOffset >= pageData.size() || pageData[pageOffset] == 0)
        {
            throw Exceptions::KeyNotFoundException();
        }

        return (*it)->data.at(pageOffset) - 1ULL;
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

    void SparseSetMemoryContainer::ResetAndWriteDenseData(NovelRT::Utilities::Span<const size_t> ids,
                                                          NovelRT::Utilities::Span<const std::byte> data)
    {
        _dense.clear();
        _dense.reserve(ids.size());
        _sparse.clear();
        _data.clear();

        for (size_t id : ids)
        {
            // TODO: This would be faster if we early aborted once we realise the minimum value on the page
            // is above the target.
            auto it = std::ranges::find_if(
                _sparse, [id](const std::unique_ptr<SparsePage>& it)
                { return it != nullptr && id >= it->minimumPageValue && id <= it->maximumPageValue; });

            if (it == _sparse.end())
            {
                const size_t pageIndex = id / SparsePage::size;
                const size_t minValue = SparsePage::size * pageIndex;

                // This is how I learned that Linux size_t is UL, not ULL. Welp. Nice bug, bro. :) - Matt J.
                const size_t maxValue =
                    minValue + std::min(SparsePage::size - size_t(1), std::numeric_limits<size_t>::max() - minValue);

                _sparse.emplace_back(
                    std::make_unique<SparsePage>(SparsePage{.data = std::vector<size_t>(SparsePage::size),
                                                            .minimumPageValue = minValue,
                                                            .maximumPageValue = maxValue}));

                it = std::prev(_sparse.end());
            }

            _dense.push_back(id);

            // Accounting for the sentinel value with the removal of the -1. - Matt J.
            (*it)->data[id - (*it)->minimumPageValue] = _dense.size();
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
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse, [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        return GetByteIteratorViewBasedOnDenseIndexUnsafe((*it)->data[key - (*it)->minimumPageValue] - 1ULL);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::operator[](size_t key) const noexcept
    {
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse, [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        return GetByteIteratorViewBasedOnDenseIndexUnsafe((*it)->data[key - (*it)->minimumPageValue] - 1ULL);
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
