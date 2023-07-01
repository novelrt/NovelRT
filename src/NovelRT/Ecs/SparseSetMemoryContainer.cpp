// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/Ecs/Ecs.h>

namespace NovelRT::Ecs
{
    SparseSetMemoryContainer::SparseSetMemoryContainer(size_t sizeOfDataTypeInBytes) noexcept
        : _dense(std::vector<size_t>{}),
          _sparse(std::vector<size_t>{}),
          _data(std::vector<uint8_t>{}),
          _sizeOfDataTypeInBytes(sizeOfDataTypeInBytes)
    {
    }

    size_t SparseSetMemoryContainer::GetStartingByteIndexForDenseIndex(size_t denseIndex) const noexcept
    {
        return _sizeOfDataTypeInBytes * denseIndex;
    }

    uint8_t* SparseSetMemoryContainer::GetDataObjectStartAtIndex(size_t location) noexcept
    {
        return _data.data() + (location * _sizeOfDataTypeInBytes);
    }

    void SparseSetMemoryContainer::InsertInternal(size_t key, const void* value)
    {
        if (_sparse.size() <= key)
        {
            _sparse.resize(key + 1);
        }

        _dense.push_back(key);
        _sparse[key] = _dense.size() - 1;
        _data.resize(GetStartingByteIndexForDenseIndex(_dense.size()));
        auto dataPtr = GetDataObjectStartAtIndex(_dense.size() - 1);
        NovelRT::Utilities::Memory::Copy(dataPtr, _sizeOfDataTypeInBytes, value, _sizeOfDataTypeInBytes);
    }

    void SparseSetMemoryContainer::Insert(size_t key, const void* value)
    {
        if (ContainsKey(key))
        {
            throw Exceptions::DuplicateKeyException();
        }

        InsertInternal(key, value);
    }

    bool SparseSetMemoryContainer::TryInsert(size_t key, const void* value) noexcept
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
        if (!ContainsKey(key))
        {
            throw Exceptions::KeyNotFoundException();
        }

        size_t indexCutoff = _sparse[key];
        auto byteIndex = GetStartingByteIndexForDenseIndex(indexCutoff);

        _data.erase(_data.begin() + byteIndex, _data.begin() + (byteIndex + _sizeOfDataTypeInBytes));

        // the rest should be exception-free. :D
        _dense.erase(_dense.begin() + indexCutoff);

        _sparse[key] = 0;

        if (!_dense.empty())
        {
            auto bla = _sparse.rbegin().base();
            std::optional<std::vector<size_t>::iterator> targetStart{};
            size_t currentValue = 0;
            size_t finalDenseSize = _dense.size();
            for (auto it = _sparse.rbegin() + key; it != _sparse.rend(); it++)
            {
                currentValue = *it;
                if (currentValue < finalDenseSize && _dense[currentValue] == currentValue)
                {
                    targetStart = it.base();
                    break;
                }
            }

            if (targetStart.has_value() && targetStart.value() != _sparse.end())
            {
                _sparse.erase(targetStart.value(), _sparse.end());
            }
        }
        else
        {
            _sparse.clear();
        }

        for (auto&& index : _sparse)
        {
            if (index < indexCutoff || index == 0)
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

        return SparseSetMemoryContainer::ByteIteratorView(_data.begin() + GetStartingByteIndexForDenseIndex(denseIndex),
                                                          _sizeOfDataTypeInBytes);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::GetByteIteratorViewBasedOnDenseIndex(
        size_t denseIndex) const
    {
        return SparseSetMemoryContainer::ConstByteIteratorView(
            _data.cbegin() + GetStartingByteIndexForDenseIndex(denseIndex), _sizeOfDataTypeInBytes);
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::GetByteIteratorViewBasedOnDenseIndexUnsafe(
        size_t denseIndex) noexcept
    {
        return SparseSetMemoryContainer::ByteIteratorView(_data.begin() + GetStartingByteIndexForDenseIndex(denseIndex),
                                                          _sizeOfDataTypeInBytes);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::
        GetByteIteratorViewBasedOnDenseIndexUnsafe(size_t denseIndex) const noexcept
    {
        return SparseSetMemoryContainer::ConstByteIteratorView(
            _data.cbegin() + GetStartingByteIndexForDenseIndex(denseIndex), _sizeOfDataTypeInBytes);
    }

    size_t SparseSetMemoryContainer::Length() const noexcept
    {
        return _dense.size();
    }

    void SparseSetMemoryContainer::ResetAndWriteDenseData(NovelRT::Utilities::Misc::Span<const size_t> ids,
                                                          NovelRT::Utilities::Misc::Span<const uint8_t> data)
    {
        _dense.clear();
        _dense.resize(ids.size());
        _sparse.clear();
        _data.clear();
        _data.resize(data.size());

        const size_t denseSize = sizeof(size_t) * ids.size();
        const size_t dataSize = sizeof(uint8_t) * data.size();

        NovelRT::Utilities::Memory::Copy(_dense.data(), denseSize, ids.data(), denseSize);
        NovelRT::Utilities::Memory::Copy(_data.data(), dataSize, data.data(), dataSize);

        for (size_t denseIndex = 0; denseIndex < _dense.size(); denseIndex++)
        {
            size_t id = _dense[denseIndex];
            if (_sparse.size() <= id)
            {
                _sparse.resize(id + 1);
            }

            _sparse[id] = denseIndex;
        }
    }

    void SparseSetMemoryContainer::ResetAndWriteDenseData(const size_t* ids, size_t length, const uint8_t* data)
    {
        ResetAndWriteDenseData(
            NovelRT::Utilities::Misc::Span<const size_t>(ids, length),
            NovelRT::Utilities::Misc::Span<const uint8_t>(data, length * GetSizeOfDataTypeInBytes()));
    }

    SparseSetMemoryContainer::ByteIteratorView SparseSetMemoryContainer::operator[](size_t key) noexcept
    {
        return GetByteIteratorViewBasedOnDenseIndexUnsafe(_sparse[key]);
    }

    SparseSetMemoryContainer::ConstByteIteratorView SparseSetMemoryContainer::operator[](size_t key) const noexcept
    {
        return GetByteIteratorViewBasedOnDenseIndexUnsafe(_sparse[key]);
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
