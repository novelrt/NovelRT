// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_SPARSESETMEMORYCONTAINER_H
#define NOVELRT_SPARSESETMEMORYCONTAINER_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    class SparseSetMemoryContainer
    {
    private:
        std::vector<size_t> _dense;
        std::vector<size_t> _sparse;
        std::vector<uint8_t> _data;
        size_t _sizeOfDataTypeInBytes;

        [[nodiscard]] size_t GetStartingByteIndexForDenseIndex(size_t denseIndex) const noexcept;
        [[nodiscard]] uint8_t* GetDataObjectStartAtIndex(size_t location) noexcept;
        void InsertInternal(size_t key, const void* value);

    public:
        class ByteIteratorView
        {
        private:
            std::vector<uint8_t>::iterator _iteratorAtValue;
            size_t _sizeOfObject;

        public:
            explicit ByteIteratorView(std::vector<uint8_t>::iterator iteratorAtValue, size_t sizeOfObject) noexcept
                : _iteratorAtValue(iteratorAtValue), _sizeOfObject(sizeOfObject)
            {
            }

            [[nodiscard]] inline bool IsValid() const noexcept
            {
                return _sizeOfObject != 0;
            }

            [[nodiscard]] inline std::vector<uint8_t>::iterator GetUnderlyingIterator() const noexcept
            {
                return _iteratorAtValue;
            }

            inline void CopyFromLocation(void* outputLocation) const noexcept
            {
                std::memcpy(outputLocation, &(*_iteratorAtValue), _sizeOfObject);
            }

            inline void WriteToLocation(void* data) noexcept
            {
                std::memcpy(&(*_iteratorAtValue), data, _sizeOfObject);
            }

            [[nodiscard]] inline void* GetDataHandle() const noexcept
            {
                return &(*_iteratorAtValue);
            }

            inline void MoveNext()
            {
                _iteratorAtValue += _sizeOfObject;
            }
        };

        class ConstByteIteratorView
        {
        private:
            std::vector<uint8_t>::const_iterator _iteratorAtValue;
            size_t _sizeOfObject;

        public:
            explicit ConstByteIteratorView(std::vector<uint8_t>::const_iterator iteratorAtValue,
                                           size_t sizeOfObject) noexcept
                : _iteratorAtValue(iteratorAtValue), _sizeOfObject(sizeOfObject)
            {
            }

            [[nodiscard]] inline bool IsValid() const noexcept
            {
                return _sizeOfObject != 0;
            }

            [[nodiscard]] inline std::vector<uint8_t>::const_iterator GetUnderlyingIterator() const noexcept
            {
                return _iteratorAtValue;
            }

            inline void CopyFromLocation(void* outputLocation) const noexcept
            {
                std::memcpy(outputLocation, &(*_iteratorAtValue), _sizeOfObject);
            }

            [[nodiscard]] const void* GetDataHandle() const noexcept
            {
                return &(*_iteratorAtValue);
            }

            inline void MoveNext()
            {
                _iteratorAtValue += _sizeOfObject;
            }
        };

        class Iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = std::tuple<size_t, ByteIteratorView>;
            using pointer = std::tuple<std::vector<size_t>::iterator, ByteIteratorView>;
            using reference =
                std::tuple<size_t&, ByteIteratorView>; // TODO: size_t should proooobably still be a value here?

        private:
            pointer _ptr;

        public:
            explicit Iterator(pointer ptr) noexcept : _ptr(std::move(ptr))
            {
            }

            reference operator*() const
            {
                return std::tie(*std::get<0>(_ptr), std::get<1>(_ptr));
            }

            pointer operator->()
            {
                return _ptr;
            }

            Iterator& operator++()
            {
                std::get<0>(_ptr)++;
                std::get<1>(_ptr).MoveNext();
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs)
            {
                return std::get<0>(lhs._ptr) == std::get<0>(rhs._ptr);
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
            {
                return std::get<0>(lhs._ptr) != std::get<0>(rhs._ptr);
            }
        };

        class ConstIterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = std::tuple<size_t, ConstByteIteratorView>;
            using pointer = std::tuple<std::vector<size_t>::const_iterator, ConstByteIteratorView>;
            using reference = std::tuple<const size_t&, ConstByteIteratorView>;

        private:
            pointer _ptr;

        public:
            explicit ConstIterator(pointer ptr) noexcept : _ptr(std::move(ptr))
            {
            }

            reference operator*() const
            {
                return std::tie(*std::get<0>(_ptr), std::get<1>(_ptr));
            }

            pointer operator->()
            {
                return _ptr;
            }

            const ConstIterator& operator++()
            {
                std::get<0>(_ptr)++;
                std::get<1>(_ptr).MoveNext();
                return *this;
            }

            ConstIterator operator++(int)
            {
                ConstIterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return std::get<0>(lhs._ptr) == std::get<0>(rhs._ptr);
            }

            friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return std::get<0>(lhs._ptr) != std::get<0>(rhs._ptr);
            }
        };

        explicit SparseSetMemoryContainer(size_t sizeOfDataTypeInBytes) noexcept;

        void Insert(size_t key, const void* value);

        bool TryInsert(size_t key, const void* value) noexcept;

        void Remove(size_t key);

        bool TryRemove(size_t key) noexcept;

        void Clear() noexcept;

        [[nodiscard]] inline size_t GetSizeOfDataTypeInBytes() const noexcept
        {
            return _sizeOfDataTypeInBytes;
        }

        [[nodiscard]] bool ContainsKey(size_t key) const noexcept;

        [[nodiscard]] size_t CopyKeyBasedOnDenseIndex(size_t denseIndex) const;

        [[nodiscard]] size_t CopyKeyBasedOnDenseIndexUnsafe(size_t denseIndex) const noexcept;

        [[nodiscard]] ByteIteratorView GetByteIteratorViewBasedOnDenseIndex(size_t denseIndex);

        [[nodiscard]] ConstByteIteratorView GetByteIteratorViewBasedOnDenseIndex(size_t denseIndex) const;

        [[nodiscard]] ByteIteratorView GetByteIteratorViewBasedOnDenseIndexUnsafe(size_t denseIndex) noexcept;

        [[nodiscard]] ConstByteIteratorView GetByteIteratorViewBasedOnDenseIndexUnsafe(
            size_t denseIndex) const noexcept;

        [[nodiscard]] size_t Length() const noexcept;

        void ResetAndWriteDenseData(NovelRT::Utilities::Misc::Span<const size_t> ids,
                                    NovelRT::Utilities::Misc::Span<const uint8_t> data);

        void ResetAndWriteDenseData(const size_t* ids, size_t length, const uint8_t* data);

        [[nodiscard]] ByteIteratorView operator[](size_t key) noexcept;

        [[nodiscard]] ConstByteIteratorView operator[](size_t key) const noexcept;

        [[nodiscard]] Iterator begin() noexcept;

        [[nodiscard]] Iterator end() noexcept;

        [[nodiscard]] ConstIterator begin() const noexcept;

        [[nodiscard]] ConstIterator end() const noexcept;

        [[nodiscard]] ConstIterator cbegin() const noexcept;

        [[nodiscard]] ConstIterator cend() const noexcept;
    };
}

#endif // NOVELRT_SPARSESETMEMORYCONTAINER_H
