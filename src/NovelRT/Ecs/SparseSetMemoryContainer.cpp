// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT/Ecs/SparseSetMemoryContainer.h>
#include <NovelRT/Exceptions/DuplicateKeyException.h>
#include <NovelRT/Exceptions/MalformedAllocationException.h>
#include <NovelRT/Exceptions/OutOfMemoryException.h>

namespace NovelRT::Ecs
{
    SparseSetMemoryContainer::SparseSetMemoryContainer(size_t sizeOfDataTypeInBytes) noexcept : _dense(nullptr), _sparse(nullptr), _maximumSparseValue(0), _data(nullptr), _deallocateState(calloc(1, sizeOfDataTypeInBytes)), _dataPtrLength(0), _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes), _reallocateMemory(false)
    {
    }

    void SparseSetMemoryContainer::ValidateDataPtrLength() const
    {
        if (_data.size() != _dense.size() * _sizeOfDataTypeInBytes)
        {
            throw Exceptions::MalformedAllocationException();
        }
    }

    size_t SparseSetMemoryContainer::GetByteLength(size_t dataLength) const noexcept
    {
        return _sizeOfDataTypeInBytes * dataLength;
    }

    std::byte* SparseSetMemoryContainer::GetDataObjectStartAtIndex(size_t location) noexcept
    {
        return &_data[location * _sizeOfDataTypeInBytes];
    }

    void SparseSetMemoryContainer::InsertInternal(size_t key, std::byte* value)
    {
        if (_sparse.size() <= key)
        {
            _sparse.resize(key + 1);
        }

        _dense.push_back(key);
        _sparse[key] = _dense.size() - 1;
        _data.resize(GetByteLength(_dense.size()));
        auto dataPtr = GetDataObjectStartAtIndex(_dense.size() - 1);
        memcpy(dataPtr, value, _sizeOfDataTypeInBytes);
    }

    void SparseSetMemoryContainer::Insert(size_t key, std::byte* value)
    {
        if (ContainsKey(key))
        {
            throw Exceptions::DuplicateKeyException();
        }

        InsertInternal(key, value);
    }

    bool SparseSetMemoryContainer::TryInsert(size_t key, std::byte* value) noexcept
    {
        if (ContainsKey(key))
        {
            return false;
        }

        try
        {
            InsertInternal(key, value);
            return true;
        }
        catch (std::exception&)
        {
            return false;
        }
    }

    void SparseSetMemoryContainer::Remove(size_t key)
    {
        //this validates if the key is present and throws if it is not
        size_t indexCutoff = _sparse.at(key);

        _data.erase(_data.begin() + GetByteLength(indexCutoff), _data.begin() + GetByteLength(indexCutoff) + (_sizeOfDataTypeInBytes - 1));

        //the rest should be exception-free. :D
        _dense.erase(_dense.begin() + indexCutoff);

        _sparse[key] = 0;

        bool canResize = true;
        for (auto i = _sparse.begin() + key; i != _sparse.end(); i++)
        {
            if (*i == 0 && _dense[0] != key)
            {
                continue;
            }

            canResize = false;
            break;
        }

        if (canResize)
        {
            _sparse.erase(_sparse.begin() + key, _sparse.end());
        }

        for (auto&& index : _sparse)
        {
            if (index < indexCutoff)
            {
                continue;
            }

            index -= 1;
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
        if (key >= _sparse.size())
        {
            return false;
        }

        return _dense[_sparse[key]] == key;
    }

    size_t SparseSetMemoryContainer::CopyKeyBasedOnDenseIndex(size_t denseIndex) const
    {
        return _dense.at(denseIndex);
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::GetValueContainerBasedOnDenseIndex(size_t denseIndex) const
    {
        return SparseSetMemoryContainer::ByteIteratorView(static_cast<char*>(_data) + GetByteLength(denseIndex), _sizeOfDataTypeInBytes);
    }

    size_t SparseSetMemoryContainer::Length() const noexcept
    {
        return _dense.size();
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::operator[](size_t key) noexcept
    {
        if (!ContainsKey(key))
        {
           return ByteIteratorView(_data.end(), 0);
        }

        return GetValueContainerBasedOnDenseIndex(_sparse[key]);
    }

    // clang-format off

    SparseSetMemoryContainer::Iterator SparseSetMemoryContainer::begin() noexcept
    {
        return SparseSetMemoryContainer::Iterator(std::make_tuple(_dense.begin(), ByteIteratorView(_data.begin(), _sizeOfDataTypeInBytes)));
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
        return SparseSetMemoryContainer::ConstIterator(std::make_tuple(_dense.cbegin(), ConstByteIteratorView(_data.cbegin(), _sizeOfDataTypeInBytes)));
    }

    SparseSetMemoryContainer::ConstIterator SparseSetMemoryContainer::cend() const noexcept
    {
        return SparseSetMemoryContainer::ConstIterator(std::make_tuple(_dense.cend(), ConstByteIteratorView(_data.cend(), 0)));
    }

    // clang-format on
}



