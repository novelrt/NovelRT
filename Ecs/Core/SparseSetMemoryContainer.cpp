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

            // This has the +1 because we have to maintain 0 being the sentinel value. I think? - Matt J.
            const size_t minValue = (SparsePage::size * pageIndex) + 1ULL;
            const size_t maxValue = SparsePage::size * (pageIndex + 1ULL);

            _sparse.emplace_back(std::make_unique<SparsePage>(
                SparsePage{.data = {}, .minimumPageValue = minValue, .maximumPageValue = maxValue}));

            it = std::prev(_sparse.end());

            auto& pageData = (*it)->data;

            if (pageData.size() <= key)
            {
                pageData.resize(key + 1ULL);
            }
        }

        const size_t originalDenseSize = _dense.size();
        const size_t originalDataSize = _data.size();

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

        (*it)->data[key] = originalDenseSize;
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
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse.begin(), _sparse.end(), [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        if (it == _sparse.end())
        {
            return false;
        }

        return _dense[(*it)->data[key]] == key;
    }

    size_t SparseSetMemoryContainer::GetDenseIndex(size_t key) const
    {
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse.begin(), _sparse.end(), [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        if (it == _sparse.end())
        {
            throw Exceptions::KeyNotFoundException();
        }

        return (*it)->data.at(key);
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

                // This has the +1 because we have to maintain 0 being the sentinel value. I think? - Matt J.
                const size_t minValue = (SparsePage::size * pageIndex) + 1ULL;
                const size_t maxValue = SparsePage::size * (pageIndex + 1ULL);

                _sparse.emplace_back(std::make_unique<SparsePage>(
                    SparsePage{.data = {}, .minimumPageValue = minValue, .maximumPageValue = maxValue}));

                it = std::prev(_sparse.end());

                auto& pageData = (*it)->data;

                if (pageData.size() <= id)
                {
                    pageData.resize(id + 1ULL);
                }
            }

            _dense.push_back(id);
            (*it)->data[id] = _dense.size() - 1ULL;
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

        return GetByteIteratorViewBasedOnDenseIndexUnsafe((*it)->data[key]);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::operator[](size_t key) const noexcept
    {
        // TODO: This would be faster if we early aborted once we realise the minimum value on the page
        // is above the target.
        auto it = std::ranges::find_if(
            _sparse, [key](const std::unique_ptr<SparsePage>& it)
            { return it != nullptr && key >= it->minimumPageValue && key <= it->maximumPageValue; });

        return GetByteIteratorViewBasedOnDenseIndexUnsafe((*it)->data[key]);
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
