// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_ECS_SPARSESET_H
#define NOVELRT_ECS_SPARSESET_H

#ifndef NOVELRT_ECS_H
#error NovelRT does not support including types explicitly by default. Please include Ecs.h instead for the Ecs namespace subset.
#endif

namespace NovelRT::Ecs
{
    /**
     * @brief A custom sparse set implementation designed at storing small, blittable types.
     *
     * Please note that this storage type assumes that the component in question is a simple struct at all times.
     * The value type should not be massively complex as there may be many copy instructions that are not SIMDifiable if
     * the type is too complicated. The type TValue of the SparseSet must be trivially copyable as defined by the C++
     * language reference. This is due to the internal language binding mechanisms of NovelRT, and is enforced by a
     * check against std::is_trivally_copyable.
     *
     * @tparam TKey The type to use for the Key.
     * @tparam TValue The type to use for the value.
     */
    template<typename TKey, typename TValue> class SparseSet
    {
    private:
        SparseSetMemoryContainer _innerContainer;

    public:
        /**
         * @brief A non const iterator for traversing the keys and values of this particular SparseSet as tuple pairs.
         *
         */
        class Iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Utilities::KeyValuePair<TKey, TValue>;
            using pointer = SparseSetMemoryContainer::Iterator;
            using reference = Utilities::KeyValuePair<TKey, TValue&>;

        private:
            pointer _ptr;

        public:
            Iterator(pointer ptr) : _ptr(ptr)
            {
            }

            reference operator*() const
            {
                auto tuple = *_ptr;
                return reference{std::get<0>(tuple), *reinterpret_cast<TValue*>(std::get<1>(tuple).GetDataHandle())};
            }

            pointer operator->()
            {
                return _ptr;
            }

            Iterator& operator++()
            {
                _ptr++;
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
                return lhs._ptr == rhs._ptr;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        };

        /**
         * @brief A const iterator for traversing the keys and values of this particular SparseSet as tuple pairs in a
         * read-only fashion.
         *
         */
        class ConstIterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = Utilities::KeyValuePair<TKey, TValue>;
            using pointer = SparseSetMemoryContainer::ConstIterator;
            using reference = Utilities::KeyValuePair<TKey, const TValue&>;

        private:
            pointer _ptr;

        public:
            ConstIterator(pointer ptr) : _ptr(ptr)
            {
            }

            reference operator*() const
            {
                auto tuple = *_ptr;
                return reference{std::get<0>(tuple),
                                 *reinterpret_cast<const TValue*>(std::get<1>(tuple).GetDataHandle())};
            }

            const ConstIterator& operator++()
            {
                _ptr++;
                return *this;
            }

            ConstIterator operator++(int)
            {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            friend bool operator==(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return lhs._ptr == rhs._ptr;
            }

            friend bool operator!=(const ConstIterator& lhs, const ConstIterator& rhs)
            {
                return lhs._ptr != rhs._ptr;
            }
        };

        /**
         * @brief Constructs a new instance of SparseSet with the given type parameters.
         *
         */
        SparseSet() noexcept : _innerContainer(SparseSetMemoryContainer(sizeof(TValue)))
        {
            static_assert(std::is_trivially_copyable<TValue>::value,
                          "Value type must be trivially copyable for use with a SparseSet. See the documentation for "
                          "more information.");
        }

        /**
         * @brief Inserts a new key with paired with an initial value into the set. All keys must be unique.
         *
         * @param key The new key to insert.
         * @param value The initial value to associate with the key.
         *
         * @exception NovelRT::Core::Exceptions::DuplicateKeyException when a duplicate key is provided.
         * @exception std::bad_alloc if there is no memory left to allocate from the system to this SparseSet.
         */
        void Insert(TKey key, TValue value)
        {
            _innerContainer.Insert(key, &value);
        }

        /**
         * @brief Attempts to insert a new key paired with an initial value into the set. All keys must be unique.
         *
         * @param key The new key to insert.
         * @param value The initial value to associate with the key.
         *
         * @return true when the pair is successfully inserted.
         * @return false when the pair could not be inserted as dictated by SparseSet::ContainsKey.
         */
        bool TryInsert(TKey key, TValue value) noexcept
        {
            return _innerContainer.TryInsert(key, &value);
        }

        /**
         * @brief Removes a given key and its associated value from the set.
         *
         * @param key The key to remove.
         *
         * @exception std::out_of_range if the key is not present within the SparseSet.
         */
        void Remove(TKey key)
        {
            _innerContainer.Remove(key);
        }

        /**
         * @brief Attempts to remove the given key from the SparseSet with additional safety checks to ensure it is an
         * exceptionless operation.
         *
         * @param key The key to remove.
         * @return true if the key was successfully removed.
         * @return false if SparseSet::ContainsKey returns false.
         */
        bool TryRemove(TKey key) noexcept
        {
            return _innerContainer.TryRemove(key);
        }

        /**
         * @brief Erases all data from the SparseSet.
         *
         */
        void Clear() noexcept
        {
            _innerContainer.Clear();
        }

        /**
         * @brief Checks if the key is present within the SparseSet.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param key The key to look for.
         * @return true if the key is present.
         * @return false if the key was not found.
         */
        [[nodiscard]] bool ContainsKey(TKey key) const noexcept
        {
            return _innerContainer.ContainsKey(key);
        }

        /**
         * @brief Copies the key out of the sparse set at the given dense index.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param denseIndex The location in the dense data to copy from.
         * @return The key at the specified dense location.
         *
         * @exception std::out_of_range if the specified dense index does not exist within the SparseSet.
         */
        [[nodiscard]] TKey CopyKeyBasedOnDenseIndex(size_t denseIndex) const
        {
            return _innerContainer.CopyKeyBasedOnDenseIndex(denseIndex);
        }

        /**
         * @brief Copies the key out of the sparse set at the given dense index.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method. This method assumes that the dense index is guaranteed to exist. If it does not then the
         * behaviour is undefined. You can guarantee the existence of the dense index by comparing the dense index being
         * used to the length of the SparseSet. See SparseSet::Length for more information.
         *
         * @param denseIndex The location in the dense data to copy from.
         * @return The key at the specified dense location.
         */
        [[nodiscard]] TKey CopyKeyBasedOnDenseIndexUnsafe(size_t denseIndex) const noexcept
        {
            return _innerContainer.CopyKeyBasedOnDenseIndexUnsafe(denseIndex);
        }

        /**
         * @brief Copies the value out of the sparse set at the given dense index.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @param denseIndex The location in the dense data to copy from.
         * @return The value at the specified dense location.
         *
         * @exception std::out_of_range if the specified dense index does not exist within the SparseSet.
         */
        [[nodiscard]] TValue CopyValueBasedOnDenseIndex(size_t denseIndex) const
        {
            return *reinterpret_cast<const TValue*>(
                _innerContainer.GetByteIteratorViewBasedOnDenseIndex(denseIndex).GetDataHandle());
        }

        /**
         * @brief Copies the value out of the sparse set at the given dense index.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method. This method assumes that the dense index is guaranteed to exist. IF it does not then the
         * behaviour is undefined. You can guarantee the existence of the dense index by comparing the dense index being
         * used to the length of the SparseSet. See SparseSet::Length for more information.
         *
         * @param denseIndex The location in the dense data to copy from.
         * @return The value at the specified dense location.
         */
        [[nodiscard]] TValue CopyValueBasedOnDenseIndexUnsafe(size_t denseIndex) const noexcept
        {
            return *reinterpret_cast<const TValue*>(
                _innerContainer.GetByteIteratorViewBasedOnDenseIndexUnsafe(denseIndex).GetDataHandle());
        }

        /**
         * @brief Gets the current length of the SparseSet based on the dense data.
         *
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return The length of the SparseSet<TKey, TValue>.
         */
        [[nodiscard]] size_t Length() const noexcept
        {
            return _innerContainer.Length();
        }

        /**
         * @brief Fetches the value associated with the provided key.
         *
         * @param key The target key to search for.
         * @return The value as a mutable reference.
         *
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         * This operator shares similar behaviour to that of std::vector. Specifically, if an invalid key is provided,
         * then the resulting behaviour will be undefined.
         */
        [[nodiscard]] TValue& operator[](TKey key) noexcept
        {
            return *reinterpret_cast<TValue*>(_innerContainer[key].GetDataHandle());
        }

        /**
         * @brief Fetches the value associated with the provided key.
         *
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         *
         * @param key The target key to search for.
         * @return The value as a const reference.
         *
         * @exception std::out_of_range if the specified key does not exist within the SparseSet.
         */
        [[nodiscard]] const TValue& operator[](TKey key) const noexcept
        {
            return *reinterpret_cast<const TValue*>(_innerContainer[key].GetDataHandle());
        }

        /**
         * @brief Gets the beginning forward iterator state for this SparseSet.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         *
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] SparseSet<TKey, TValue>::Iterator begin() noexcept
        {
            return SparseSet<TKey, TValue>::Iterator(_innerContainer.begin());
        }

        /**
         * @brief Gets the ending forward iterator state for this SparseSet.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         *
         * @return SparseSet::ConstIterator starting at the end.
         */
        [[nodiscard]] SparseSet<TKey, TValue>::Iterator end() noexcept
        {
            return SparseSet<TKey, TValue>::Iterator(_innerContainer.end());
        }

        /**
         * @brief Gets the beginning forward const iterator state for this SparseSet.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         *
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] SparseSet<TKey, TValue>::ConstIterator begin() const noexcept
        {
            return SparseSet<TKey, TValue>::ConstIterator(_innerContainer.begin());
        }

        /**
         * @brief Gets the ending forward const iterator state for this SparseSet.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * While this method is not const, it does not modify the SparseSet itself.
         * Calling this without using the result has no effect and introduces overhead for calling a method.
         *
         * @return SparseSet::ConstIterator starting at the end.
         */
        [[nodiscard]] SparseSet<TKey, TValue>::ConstIterator end() const noexcept
        {
            return SparseSet<TKey, TValue>::ConstIterator(_innerContainer.end());
        }

        /**
         * @brief Gets the beginning forward const iterator state for this SparseSet.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return SparseSet::ConstIterator starting at the beginning.
         */
        [[nodiscard]] SparseSet<TKey, TValue>::ConstIterator cbegin() const noexcept
        {
            return SparseSet<TKey, TValue>::ConstIterator(_innerContainer.cbegin());
        }

        /**
         * @brief Gets the ending forward const iterator state for this SparseSet.
         *
         * This function is under special formatting so that range-based for loops are supported.
         * This is a pure method. Calling this without using the result has no effect and introduces overhead for
         * calling a method.
         *
         * @return SparseSet::ConstIterator starting at the end.
         */
        [[nodiscard]] SparseSet<TKey, TValue>::ConstIterator cend() const noexcept
        {
            return SparseSet<TKey, TValue>::ConstIterator(_innerContainer.cend());
        }
    };
}

#endif //! NOVELRT_ECS_SPARSESET_H
